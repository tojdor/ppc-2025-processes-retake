#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "muhammadkhon_i_max_matrix_elem/common/include/common.hpp"
#include "muhammadkhon_i_max_matrix_elem/mpi/include/ops_mpi.hpp"
#include "muhammadkhon_i_max_matrix_elem/seq/include/ops_seq.hpp"
#include "util/include/func_test_util.hpp"
#include "util/include/util.hpp"

namespace muhammadkhon_i_max_matrix_elem {

class MuhammadkhonIMaxMatrixElemTests : public ppc::util::BaseRunFuncTests<InType, OutType, TestType> {
 protected:
  void SetUp() override {
    auto params = std::get<static_cast<std::size_t>(ppc::util::GTestParamIndex::kTestParams)>(GetParam());
    test_case_ = std::get<0>(params);
    expected_validation_ = true;

    switch (test_case_) {
      case 1:
        input_data_.rows = 2;
        input_data_.columns = 2;
        input_data_.data = {1, 2, 3, 4};
        expected_max_ = 4;
        break;
      case 2:
        input_data_.rows = 3;
        input_data_.columns = 2;
        input_data_.data = {-1, -5, 8, -3, 0, 7};
        expected_max_ = 8;
        break;
      case 3:
        input_data_.rows = 1;
        input_data_.columns = 1;
        input_data_.data = {42};
        expected_max_ = 42;
        break;
      case 4:
        input_data_.rows = 2;
        input_data_.columns = 3;
        input_data_.data = {5, 5, 5, 5, 10, 5};
        expected_max_ = 10;
        break;
      case 5:
        input_data_.rows = 4;
        input_data_.columns = 3;
        input_data_.data = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        expected_max_ = 0;
        break;
      case 6:
        input_data_.rows = 2;
        input_data_.columns = 4;
        input_data_.data = {-10, -20, -5, -1, -15, -25, -30, -2};
        expected_max_ = -1;
        break;
      case 7:
        input_data_.rows = 3;
        input_data_.columns = 3;
        input_data_.data = {100, 200, 150, 300, 250, 350, 400, 450, 500};
        expected_max_ = 500;
        break;
      case 8:
        input_data_.rows = 1;
        input_data_.columns = 5;
        input_data_.data = {7, 7, 7, 7, 7};
        expected_max_ = 7;
        break;

      default:
        throw std::runtime_error("Unknown test case");
    }
  }

  bool CheckTestOutputData(OutType &output_data) final {
    if (!expected_validation_) {
      return false;
    }
    return (expected_max_ == output_data);
  }

  InType GetTestInputData() final {
    return input_data_;
  }

 public:
  static std::string PrintTestParam(const TestType &test_param) {
    return "TestCase_" + std::to_string(std::get<0>(test_param)) + "_" + std::get<1>(test_param);
  }

 private:
  InType input_data_{};
  int expected_max_ = 0;
  int test_case_ = 0;
  bool expected_validation_ = true;
};

namespace {

TEST_P(MuhammadkhonIMaxMatrixElemTests, MatmulFromPic) {
  ExecuteTest(GetParam());
}

const std::array<TestType, 8> kTestParam = {
    std::make_tuple(1, "2x2_matrix"),       std::make_tuple(2, "with_negatives"),  std::make_tuple(3, "single_element"),
    std::make_tuple(4, "repeated_max"),     std::make_tuple(5, "all_zeros"),       std::make_tuple(6, "all_negatives"),
    std::make_tuple(7, "3x3_large_values"), std::make_tuple(8, "1x5_same_values"),
};

const auto kTestTasksList = std::tuple_cat(ppc::util::AddFuncTask<MuhammadkhonIMaxMatrixElemMPI, InType>(
                                               kTestParam, PPC_SETTINGS_muhammadkhon_i_max_matrix_elem),
                                           ppc::util::AddFuncTask<MuhammadkhonIMaxMatrixElemSEQ, InType>(
                                               kTestParam, PPC_SETTINGS_muhammadkhon_i_max_matrix_elem));

const auto kGtestValues = ppc::util::ExpandToValues(kTestTasksList);
const auto kPerfTestName = MuhammadkhonIMaxMatrixElemTests::PrintFuncTestName<MuhammadkhonIMaxMatrixElemTests>;

INSTANTIATE_TEST_SUITE_P(MatrixMaxTests, MuhammadkhonIMaxMatrixElemTests, kGtestValues, kPerfTestName);

}  // namespace

}  // namespace muhammadkhon_i_max_matrix_elem
