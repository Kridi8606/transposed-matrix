#include <iostream>

int **createMatrix(size_t m, size_t n);
void clearMatrix(int **matrix, size_t m);

int main()
{
  size_t m = 0;
  size_t n = 0;
  std::cin >> m >> n;
  if (std::cin.fail()) {
    return 1;
  }

  int **matrix = nullptr;
  try {
    matrix = createMatrix(m, n);
  } catch (...) {
    return 2;
  }
  int number = 0;

  std::cout << std::endl;
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      std::cin >> number;
      if (std::cin.fail()) {
        clearMatrix(matrix, m);
        return 1;
      }
      matrix[i][j] = number;
    }
  }

  std::cout << std::endl;
  for (size_t j = 0; j < n; j++) {
    for (size_t i = 0; i < m; i++) {
      std::cout << matrix[i][j] << "\t";
    }
    std::cout << std::endl;
  }

  clearMatrix(matrix, m);
  return 0;
}

int **createMatrix(size_t m, size_t n)
{
  int **matrix = new int *[m] {};

  try {
    for (size_t i = 0; i < m; i++) {
      matrix[i] = new int[n];
    }
  } catch (...) {
    for (size_t i = 0; i < m; i++) {
      delete[] matrix[i];
    }

    delete[] matrix;
    throw;
  }

  return matrix;
}

void clearMatrix(int **matrix, size_t m)
{
  for (size_t i = 0; i < m; i++) {
    delete[] matrix[i];
  }

  delete[] matrix;
}
