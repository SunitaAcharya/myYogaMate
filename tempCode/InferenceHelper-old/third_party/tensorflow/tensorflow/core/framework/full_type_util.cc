/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/core/framework/full_type_util.h"

#include <algorithm>
#include <string>

#include "absl/container/flat_hash_map.h"
#include "tensorflow/core/framework/attr_value.pb.h"
#include "tensorflow/core/framework/full_type.pb.h"
#include "tensorflow/core/framework/node_def.pb.h"
#include "tensorflow/core/framework/node_def_util.h"
#include "tensorflow/core/framework/op_def.pb.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/platform/errors.h"
#include "tensorflow/core/platform/statusor.h"
#include "tensorflow/core/protobuf/error_codes.pb.h"

namespace tensorflow {

namespace full_type {

OpTypeConstructor Nullary(FullTypeId t) {
  return [t](OpDef* op_def) {
    FullTypeDef* tdef =
        op_def->mutable_output_arg(0)->mutable_experimental_full_type();
    tdef->set_type_id(t);
    return Status::OK();
  };
}

OpTypeConstructor Unary(FullTypeId t, const string& var_name) {
  return [t, var_name](OpDef* op_def) {
    FullTypeDef* tdef =
        op_def->mutable_output_arg(0)->mutable_experimental_full_type();
    tdef->set_type_id(t);

    FullTypeDef* arg = tdef->add_args();
    arg->set_type_id(TFT_VAR);
    arg->set_s(var_name);

    return Status::OK();
  };
}

OpTypeConstructor UnaryGeneric(FullTypeId t) {
  return [t](OpDef* op_def) {
    FullTypeDef* tdef =
        op_def->mutable_output_arg(0)->mutable_experimental_full_type();
    tdef->set_type_id(t);

    FullTypeDef* arg = tdef->add_args();
    arg->set_type_id(TFT_ANY);

    return Status::OK();
  };
}

OpTypeConstructor UnaryTensorContainer(FullTypeId t, FullTypeId dtype) {
  return [t, dtype](OpDef* op_def) {
    FullTypeDef* tdef =
        op_def->mutable_output_arg(0)->mutable_experimental_full_type();
    tdef->set_type_id(t);

    FullTypeDef* arg = tdef->add_args();
    arg->set_type_id(TFT_TENSOR);
    FullTypeDef* targ = arg->add_args();
    targ->set_type_id(dtype);

    return Status::OK();
  };
}

OpTypeConstructor UnaryTensorContainer(FullTypeId t, const string& var_name) {
  return [t, var_name](OpDef* op_def) {
    FullTypeDef* tdef =
        op_def->mutable_output_arg(0)->mutable_experimental_full_type();
    tdef->set_type_id(t);

    FullTypeDef* targ = tdef->add_args();
    targ->set_type_id(TFT_TENSOR);
    FullTypeDef* varg = targ->add_args();
    varg->set_type_id(TFT_VAR);
    varg->set_s(var_name);

    return Status::OK();
  };
}

OpTypeConstructor VariadicTensorContainer(FullTypeId t,
                                          const string& var_name) {
  return [t, var_name](OpDef* op_def) {
    FullTypeDef* tdef =
        op_def->mutable_output_arg(0)->mutable_experimental_full_type();
    tdef->set_type_id(t);

    FullTypeDef* for_each = tdef->add_args();
    for_each->set_type_id(TFT_FOR_EACH);
    for_each->add_args()->set_type_id(TFT_PRODUCT);

    FullTypeDef* tpl = for_each->add_args();
    tpl->set_type_id(TFT_TENSOR);
    FullTypeDef* targ = tpl->add_args();
    targ->set_type_id(TFT_VAR);
    targ->set_s(var_name);

    FullTypeDef* tvar = for_each->add_args();
    tvar->set_type_id(TFT_VAR);
    tvar->set_s(var_name);

    return Status::OK();
  };
}

namespace {

inline bool ReduceVariantTensor(FullTypeDef& t) {
  // Special case for DT_VARIANT tensors. We leave those unset to avoid even
  // more special casing downstream.
  if (t.type_id() == TFT_TENSOR && t.args_size() &&
      t.args(0).type_id() == TFT_LEGACY_VARIANT) {
    t.Clear();
    return true;
  }
  return false;
}

typedef absl::flat_hash_map<StringPiece, const AttrValue*> AttrMap;

inline Status SubstituteFromAttrs(AttrMap& attrs, FullTypeDef& t);

Status SubstituteVar(AttrMap& attrs, FullTypeDef& t) {
  DCHECK_EQ(t.args_size(), 0);

  StringPiece var_name = t.s();
  if (!attrs.contains(var_name)) {
    return Status(
        error::INVALID_ARGUMENT,
        absl::StrCat("could not find an attribute for key '", var_name, "'"));
  }
  const AttrValue* attr = attrs.at(var_name);

  const auto attr_type = attr->value_case();
  if (attr_type == AttrValue::kType) {
    map_dtype_to_tensor(attr->type(), t);
  } else if (attr_type == AttrValue::kList) {
    const auto& attr_list = attr->list();
    if (attr_list.type_size() != 1) {
      return Status(error::UNIMPLEMENTED,
                    absl::StrCat("lists or other than one type element\n",
                                 attr_list.DebugString(), "\nkey=", var_name));
    }
    map_dtype_to_tensor(attr_list.type(0), t);
  } else {
    return Status(error::UNIMPLEMENTED,
                  absl::StrCat("unsupported attribute type ",
                               attr->DebugString(), " for name ", var_name));
  }
  t.clear_s();
  return Status::OK();
}

Status SubstituteForEach(AttrMap& attrs, FullTypeDef& t) {
  DCHECK_EQ(t.args_size(), 3);

  const auto& cont = t.args(0);
  const auto& tmpl = t.args(1);
  const auto& t_var = t.args(2);

  StringPiece var_name = t_var.s();
  if (!attrs.contains(var_name)) {
    return Status(
        error::INVALID_ARGUMENT,
        absl::StrCat("could not find an attribute for key '", var_name, "'"));
  }
  const AttrValue* attr = attrs.at(var_name);

  FullTypeDef result;
  result.set_type_id(cont.type_id());

  const auto attr_type = attr->value_case();
  if (attr_type == AttrValue::kType) {
    FullTypeDef* target = result.add_args();
    *target = tmpl;
    TF_RETURN_WITH_CONTEXT_IF_ERROR(
        SubstituteFromAttrs(attrs, *target), "while substituting '", var_name,
        "' from\n", attr->DebugString(), "\ninto ", target->DebugString());

  } else if (attr_type == AttrValue::kList) {
    const auto& attr_list = attr->list();
    int tsize = attr_list.type_size();
    if (tsize == 0) {
      return Status(error::UNIMPLEMENTED,
                    absl::StrCat("unsupported list attribute type\n",
                                 attr_list.DebugString(), "\nkey=", var_name));
    }
    AttrValue replacement;
    attrs[var_name] = &replacement;
    for (int i = 0; i < tsize; i++) {
      replacement.set_type(attr_list.type(i));
      FullTypeDef* target = result.add_args();
      *target = tmpl;
      TF_RETURN_WITH_CONTEXT_IF_ERROR(SubstituteFromAttrs(attrs, *target),
                                      "while substituting '", var_name,
                                      "' from\n", attr->DebugString(), "\n[", i,
                                      "] into\n", target->DebugString());
    }
    // In case of error, it's ok for the attributes map to remain in an invalid
    // state.
    attrs[var_name] = attr;

  } else {
    return Status(error::UNIMPLEMENTED,
                  absl::StrCat("unsupported attribute type\n",
                               attr->DebugString(), "\nfor name ", var_name));
  }
  t = result;
  return Status::OK();
}

Status SubstituteGeneric(AttrMap& attrs, FullTypeDef& t) {
  int nargs = t.args_size();
  for (int j = 0; j < nargs; j++) {
    TF_RETURN_WITH_CONTEXT_IF_ERROR(
        SubstituteFromAttrs(attrs, *(t.mutable_args(j))),
        "while substituting arg ", j, ": ", t.args(j).DebugString());
  }
  return Status::OK();
}

inline Status SubstituteFromAttrs(AttrMap& attrs, FullTypeDef& t) {
  // Resolve dependent types. The convention for op registrations is to use
  // attributes as type variables.
  // See https://www.tensorflow.org/guide/create_op#type_polymorphism.
  // Once the op signature can be defined entirely in FullType, this
  // convention can be deprecated.
  //
  // Note: While this code performs some basic verifications, it generally
  // assumes consistent op defs and attributes. If more complete
  // verifications are needed, they should be done by separately, and in a
  // way that can be reused for type inference.
  switch (t.type_id()) {
    case TFT_VAR:
      return SubstituteVar(attrs, t);

    case TFT_FOR_EACH:
      return SubstituteForEach(attrs, t);

    default:
      return SubstituteGeneric(attrs, t);
  }
  return Status::OK();
}

}  // namespace

Status SpecializeType(const AttrSlice& attrs, const OpDef& op_def,
                      FullTypeDef& target) {
  target.set_type_id(TFT_PRODUCT);

  AttrMap map;
  for (const auto& attr : attrs) {
    map.emplace(attr.first, &attr.second);
  }

  int nargs = op_def.output_arg_size();
  for (int i = 0; i < nargs; i++) {
    auto& t = *(target.add_args());
    t = op_def.output_arg(i).experimental_full_type();
    TF_RETURN_WITH_CONTEXT_IF_ERROR(
        SubstituteFromAttrs(map, t), "while expanding vars of\n",
        t.DebugString(), "\nfrom\n", attrs.SummarizeNode());
    ReduceVariantTensor(t);
  }

  return Status::OK();
}

const FullTypeDef& GetArgDefaultUnset(const FullTypeDef& t, int i) {
  static FullTypeDef* unset_type = []() {
    FullTypeDef* t = new FullTypeDef();
    return t;
  }();

  if (i < t.args_size()) {
    return t.args(i);
  }
  return *unset_type;
}

const FullTypeDef& GetArgDefaultAny(const FullTypeDef& t, int i) {
  static FullTypeDef* any_type = []() {
    FullTypeDef* t = new FullTypeDef();
    t->set_type_id(TFT_ANY);
    return t;
  }();

  if (i < t.args_size()) {
    const FullTypeDef& f_val = t.args(i);
    if (f_val.type_id() == TFT_UNSET) {
      return *any_type;
    }
    return f_val;
  }
  return *any_type;
}

bool IsEqual(const FullTypeDef& lhs, const FullTypeDef& rhs) {
  if (lhs.type_id() != rhs.type_id()) {
    return false;
  }
  const auto& lhs_s = lhs.s();
  const auto& rhs_s = rhs.s();
  if (lhs_s.empty()) {
    if (!rhs_s.empty()) {
      return false;
    }
  } else if (rhs_s != lhs_s) {
    return false;
  }
  for (int i = 0; i < std::max(lhs.args_size(), rhs.args_size()); i++) {
    const FullTypeDef& lhs_arg = GetArgDefaultAny(lhs, i);
    const FullTypeDef& rhs_arg = GetArgDefaultAny(rhs, i);

    if (!IsEqual(lhs_arg, rhs_arg)) {
      return false;
    }
  }
  return true;
}

bool IsSubtype(const FullTypeDef& lhs, const FullTypeDef& rhs, bool covariant) {
  // Rule: ANY is a supertype of all types.
  if (rhs.type_id() == TFT_ANY) {
    return true;
  }
  // Compatibility rule: UNSET is treated as ANY for the purpose of subtyping.
  if (rhs.type_id() == TFT_UNSET) {
    return true;
  }
  // Default rule: type IDs must match.
  if (lhs.type_id() != rhs.type_id()) {
    return false;
  }

  for (int i = 0; i < std::max(lhs.args_size(), rhs.args_size()); i++) {
    const FullTypeDef& lhs_arg = GetArgDefaultAny(lhs, i);
    const FullTypeDef& rhs_arg = GetArgDefaultAny(rhs, i);

    if (covariant) {
      if (!IsSubtype(lhs_arg, rhs_arg)) {
        return false;
      }
    } else {
      if (!IsSubtype(rhs_arg, lhs_arg)) {
        return false;
      }
    }
  }

  // Invariant: type IDs are eaqual, and all args are subtype of one another.
  return true;
}

}  // namespace full_type

}  // namespace tensorflow