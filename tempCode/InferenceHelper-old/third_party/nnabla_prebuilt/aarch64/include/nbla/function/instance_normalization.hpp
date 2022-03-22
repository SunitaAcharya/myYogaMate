// Copyright 2021 Sony Corporation.
// Copyright 2021 Sony Group Corporation.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef NBLA_FUNCTION_INSTANCE_NORMALIZATION_HPP
#define NBLA_FUNCTION_INSTANCE_NORMALIZATION_HPP

#include <nbla/cpu.hpp>
#include <nbla/function.hpp>
#include <nbla/function_registry.hpp>

namespace nbla {

NBLA_REGISTER_FUNCTION_HEADER(InstanceNormalization, int, const vector<int> &,
                              float, bool, bool);

/**
    @todo Write doc.

Inputs:

Outputs:

\ingroup FunctionImplGrp
 */
template <typename T>
class InstanceNormalization
    : public BaseFunction<int, const vector<int> &, float, bool, bool> {
protected:
  int channel_axis_;
  vector<int> batch_axis_;
  float eps_;
  bool no_scale_, no_bias_;

  int beta_idx_, gamma_idx_;
  bool need_beta_broadcast_, need_gamma_broadcast_;
  shared_ptr<Function> f_broadcast_beta_, f_broadcast_gamma_;
  shared_ptr<Function> f_tensor_norm_;

public:
  InstanceNormalization(const Context &ctx, int channel_axis,
                        const vector<int> &batch_axis, float eps, bool no_scale,
                        bool no_bias)
      : BaseFunction(ctx, channel_axis, batch_axis, eps, no_scale, no_bias),
        channel_axis_(channel_axis), batch_axis_(batch_axis), eps_(eps),
        no_scale_(no_scale), no_bias_(no_bias) {}
  virtual ~InstanceNormalization() {}
  virtual shared_ptr<Function> copy() const {
    return create_InstanceNormalization(ctx_, channel_axis_, batch_axis_, eps_,
                                        no_scale_, no_bias_);
  }
  virtual int min_inputs() { return 1; }
  virtual int min_outputs() { return 1; }
  virtual vector<dtypes> in_types() {
    return vector<dtypes>{get_dtype<T>(), get_dtype<T>(), get_dtype<T>()};
  }
  virtual vector<dtypes> out_types() { return vector<dtypes>{get_dtype<T>()}; }
  virtual vector<string> allowed_array_classes() {
    return SingletonManager::get<Cpu>()->array_classes();
  }
  virtual string name() { return "InstanceNormalization"; }
  virtual bool grad_depends_output_data(int i, int o) const {
    // Gradient computation always requires output mean and var.
    return o > 0;
  }

protected:
  NBLA_API virtual void setup_impl(const Variables &inputs,
                                   const Variables &outputs);
  NBLA_API virtual void forward_impl(const Variables &inputs,
                                     const Variables &outputs);
  NBLA_API virtual void backward_impl(const Variables &inputs,
                                      const Variables &outputs,
                                      const vector<bool> &propagate_down,
                                      const vector<bool> &accum);
  virtual bool grad_depends_input_data_impl(int i, int j) const {
    if (i == 0) {
      return true;
    }
    if (j == 0) {
      return true;
    }
    if (i == j) {
      return true;
    }
    return false;
  }
};
}
#endif
