- Student: <Мухаммадхон Исрам Абдулманон>, group <3823Б1ПР5>
- Technology: <SEQ | MPI>
- Variant: <13>

## 1. Introduction

мотивация: ускорение поиска максимального элемента в больших
матрицах с помощью распределения вычислений между несколькими
процессами.

проблема: последовательный поиск максимума в матрицах большого
размера занимает значительное время.

цель: ускорить высиления за счет параллельной обработки данных.

## 2. Problem Statement

задача: найти максимальный элемент в матрице размером Matrix[rows,
columns].

Input/Output: на вход подаётся структура Matrix с данными, на выход 
одно целое число, максимальный элемент матрицы.

## 3. Baseline Algorithm (Sequential)

Describe the base algorithm with enough detail to reproduce.

```cpp
int max_value = matrix[0];
for (size_t i = 1; i < matrix.size(); i++) {
    max_value = std::max(max_value, matrix[i]);
}
GetOutput() = max_value;
```

Последовательный алгоритм просто перебирает все элементы матрицы и 
выбирает наибольший.

## 4. Parallelization Scheme

data distribution:
Блочное распределение по строкам с балансировкой нагрузки для 
неравномерного деления

Сommunication pattern:

```cpp
//распределение данных
MPI_Scatterv(matrix.data(), how_many_to_one_proces.data(), offset
data(), MPI_INT, recvbuf.data(),
               how_many_to_one_proces[rank], MPI_INT, 0,
               MPI_COMM_WORLD);
//поиск локального максимума
  int local_max;
  if (!recvbuf.empty()) {
    local_max = recvbuf[0];
    for (size_t i = 1; i < recvbuf.size(); i++) {
      local_max = std::max(local_max, recvbuf[i]);
    }
  } else {
    local_max = 0;
  }
//поиск глобального максимума
  int global_max;
  MPI_Allreduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX
  MPI_COMM_WORLD);
```

 rank roles.
 Rank 0 - распределение задач
 Rank all - локальные вычисления и участие в редукции

## 5. Implementation Details

- Code structure (files, key classes/functions)
common - общие структуры данных
mpi - паралельная реализация mpi
seq - последовательная реализация
test - тесты функцианальности и производительности

```cpp
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
```

```cpp
class MuhammadkhonIMaxMatrixElemMPI : public BaseTask {
 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kMPI;
  }
  explicit MuhammadkhonIMaxMatrixElemMPI(const InType &in);

 private:
  bool ValidationImpl() override;
  bool PreProcessingImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;
};

```

```cpp
struct Matrix {
  std::vector<int> data;
  int rows;
  int columns;
};
```

- Important assumptions and corner cases
 1- матрица не должна быть пустой
 2- размер матрицы должен соответствовать rows*columns
 3- возращает 1 элемент(максимально значение в матрице)
- Memory usage considerations
 1- в mpi каждый процесс имеет только свои значения

## 6. Experimental Setup

- Процессор: intel i5
- Количество ядер: 2
- Количество потоков: 4
- ОЗУ: 8 Гб
- ОС: Linux Fedora
- Архитектура: x64

- Язык программирования: C++
- Библиотека для параллельного программирования: MPI
- Компилятор MSCV
- Тип сборки: Release

## 7. Results and Discussion

### 7.1 Correctness

Матрица размером 4000x4000.
Все тесты прошли успешно. MPI версии корректно определяют 
максимальный элемент, совпадающий с SEQ.

### 7.2 Performance

Результаты perf_tests

| Mode | Processes | AvgTime(s) | Speedup | Efficiency |
| ---- | --------- | ---------- | ------- | ---------- |
| seq  | 1         | 0.0137     | 1.00    | N/A        |
| mpi  | 1         | 0.0249     | 0.55    | 55%        |
| mpi  | 2         | 0.0150     | 0.91    | 45%        |
| mpi  | 4         | 0.0090     | 1.52    | 38%        |
| mpi  | 6         | 0.0070     | 1.96    | 33%        |
| mpi  | 8         | 0.0060     | 2.28    | 28%        |

## 8. Conclusions

ВЫВОД :использование mpi показало свою эффективность, ускорив работу 
таким образом можно сделать вывод, что распределение нагрузки на
несколько процессов является
максимально эффективным метод работы с большим количеством данных 
Наибольшая эффективность достигается на 2 процессах, однако
максимальное абсолютное ускорение на 4 процессах
Ограничения: если матрицы маленькие, то mpi является неэффективным
методом работы
Следовательно использование MPI является эффективным в условиях
больших матриц когда комуникация между процессами
не затратит времени больше, чем сама работа с данными

## 9. References

  MICROSOFT MPI - <https://learn.microsoft.com/ru-ru>
  message-passing-interface/microsoft-mpi
  Parallel Programming Course - <https://learning-process.github.io>
  parallel_programming_course/ru/index.html
  Parallel Programming 2025-2026 - <https://disk.yandex.ru/d>
  NvHFyhOJCQU65w
  stack overflow - <https://stackoverflow.com/questions>
