#pragma once

#include <string>
#include <tuple>

#include "task/include/task.hpp"

namespace muhammadkhon_i_max_matrix_elem {

struct Matrix {
  std::vector<int> data;
  int rows = 0;
  int columns = 0;
};

using InType = Matrix;
using OutType = int;
using TestType = std::tuple<int, std::string>;
using BaseTask = ppc::task::Task<InType, OutType>;

}  // namespace muhammadkhon_i_max_matrix_elem
