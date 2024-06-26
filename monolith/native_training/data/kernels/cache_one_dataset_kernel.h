// Copyright 2022 ByteDance and/or its affiliates.
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

#ifndef MONOLITH_NATIVE_TRAINING_DATA_KERNELS_CACHE_ONE_DATASET_KERNEL_H_
#define MONOLITH_NATIVE_TRAINING_DATA_KERNELS_CACHE_ONE_DATASET_KERNEL_H_

#include "tensorflow/core/framework/dataset.h"

namespace tensorflow {
namespace data {
namespace monolith_tf {

class CacheOneDatasetOp : public UnaryDatasetOpKernel {
 public:
  explicit CacheOneDatasetOp(OpKernelConstruction* ctx);

 protected:
  void MakeDataset(OpKernelContext* ctx, DatasetBase* input,
                   DatasetBase** output) override;

 private:
  class Dataset;
};

}  // namespace monolith_tf
}  // namespace data
}  // namespace tensorflow

#endif  // MONOLITH_NATIVE_TRAINING_DATA_KERNELS_CACHE_ONE_DATASET_KERNEL_H_
