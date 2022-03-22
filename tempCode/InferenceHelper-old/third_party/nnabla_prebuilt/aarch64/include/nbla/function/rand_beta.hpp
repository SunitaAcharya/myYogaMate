// Copyright 2020,2021 Sony Corporation.
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

/** RandBeta
 */
#ifndef NBLA_FUNCTION_RANDBETA_HPP
#define NBLA_FUNCTION_RANDBETA_HPP

#include <nbla/cpu.hpp>
#include <nbla/function.hpp>
#include <nbla/function_registry.hpp>

#include <random>

namespace nbla {

NBLA_REGISTER_FUNCTION_HEADER(RandBeta, float, float, const vector<int> &, int);

/**
    @todo Write doc.

Inputs:

Outputs:

\ingroup FunctionImplGrp
 */
template <typename T>
class RandBeta : public BaseFunction<float, float, const vector<int> &, int> {
protected:
  float alpha_;
  float beta_;
  const vector<int> shape_;
  int seed_;
  bool save_rng_ = false;
  std::mt19937 rgen_, rgen_for_recompute_;

public:
  RandBeta(const Context &ctx, float alpha, float beta,
           const vector<int> &shape, int seed)
      : BaseFunction(ctx, alpha, beta, shape, seed), alpha_(alpha), beta_(beta),
        shape_(shape), seed_(seed) {
    NBLA_CHECK(alpha > 0, error_code::value,
               "`alpha` (%d given) must be more than 0.", alpha);
    NBLA_CHECK(beta > 0, error_code::value,
               "`beta` (%d given) must be more than 0.", beta);
  }
  virtual ~RandBeta() {}
  virtual shared_ptr<Function> copy() const {
    return create_RandBeta(ctx_, alpha_, beta_, shape_, seed_);
  }
  virtual int min_inputs() { return 0; }
  virtual int min_outputs() { return 1; }
  virtual vector<dtypes> in_types() { return vector<dtypes>{}; }
  virtual vector<dtypes> out_types() { return vector<dtypes>{get_dtype<T>()}; }
  virtual vector<string> allowed_array_classes() {
    return SingletonManager::get<Cpu>()->array_classes();
  }
  virtual string name() { return "RandBeta"; }
  virtual bool need_setup_recompute(int o) const { return true; }
  virtual bool grad_depends_output_data(int i, int o) const { return false; }

protected:
  NBLA_API virtual void setup_impl(const Variables &inputs,
                                   const Variables &outputs);
  NBLA_API virtual void forward_impl(const Variables &inputs,
                                     const Variables &outputs);
  NBLA_API virtual void backward_impl(const Variables &inputs,
                                      const Variables &outputs,
                                      const vector<bool> &propagate_down,
                                      const vector<bool> &accum);
  NBLA_API virtual void setup_recompute_impl(const Variables &inputs,
                                             const Variables &outputs);
  NBLA_API virtual void recompute_impl(const Variables &inputs,
                                       const Variables &outputs);
  void random_beta(const Variables &inputs, const Variables &outputs,
                   std::mt19937 &rgen);
  virtual bool grad_depends_input_data_impl(int i, int j) const {
    return false;
  }
};
}
#endif
