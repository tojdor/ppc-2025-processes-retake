#include <gtest/gtest.h>

#include <vector>

#include "muhammadkhon_i_max_matrix_elem/common/include/common.hpp"
#include "muhammadkhon_i_max_matrix_elem/mpi/include/ops_mpi.hpp"
#include "muhammadkhon_i_max_matrix_elem/seq/include/ops_seq.hpp"
#include "util/include/perf_test_util.hpp"

namespace muhammadkhon_i_max_matrix_elem {

class MuhammadkhonIMaxMatrixElemPerfTests : public ppc::util::BaseRunPerfTests<InType, OutType> {
 protected:
  void SetUp() override {
    const int rows = 4000;
    const int cols = 4000;
    const int matrix_size = rows * cols;
    std::vector<int> data(matrix_size);

    for (int index = 0; index < matrix_size; ++index) {
      data[index] = (index % 10000) + 1;  // 1-10000
    }

    data[0] = 99999;
    data[matrix_size - 1] = 99999;

    input_data_.rows = rows;
    input_data_.columns = cols;
    input_data_.data = data;
    expected_max_ = 99999;
  }

  bool CheckTestOutputData(OutType &output_data) final {
    return (expected_max_ == output_data);
  }

  InType GetTestInputData() final {
    return input_data_;
  }

 private:
  InType input_data_{};
  int expected_max_ = 0;
};

TEST_P(MuhammadkhonIMaxMatrixElemPerfTests, RunPerfModes) {
  ExecuteTest(GetParam());
}

const auto kAllPerfTasks =
    ppc::util::MakeAllPerfTasks<InType, MuhammadkhonIMaxMatrixElemMPI, MuhammadkhonIMaxMatrixElemSEQ>(
        PPC_SETTINGS_muhammadkhon_i_max_matrix_elem);

const auto kGtestValues = ppc::util::TupleToGTestValues(kAllPerfTasks);

const auto kPerfTestName = MuhammadkhonIMaxMatrixElemPerfTests::CustomPerfTestName;

INSTANTIATE_TEST_SUITE_P(RunModeTests, MuhammadkhonIMaxMatrixElemPerfTests, kGtestValues, kPerfTestName);

}  // namespace muhammadkhon_i_max_matrix_elem
