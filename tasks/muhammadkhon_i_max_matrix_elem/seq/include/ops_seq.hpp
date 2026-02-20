#pragma once

#include "muhammadkhon_i_max_matrix_elem/common/include/common.hpp"
#include "task/include/task.hpp"

namespace muhammadkhon_i_max_matrix_elem {

class MuhammadkhonIMaxMatrixElemSEQ : public BaseTask {
 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kSEQ;
  }
  explicit MuhammadkhonIMaxMatrixElemSEQ(const InType &in);

 private:
  bool ValidationImpl() override;
  bool PreProcessingImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;
};

}  // namespace muhammadkhon_i_max_matrix_elem
