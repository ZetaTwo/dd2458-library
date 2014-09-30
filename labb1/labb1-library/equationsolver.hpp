// Linear equation solver (broken)
// -----------------------------------------
// Authors: Magnus Olsson  (magolsso@kth.se)
//          Calle Svensson (carlsven@kth.se)

#include <vector>
#include <stdexcept>

enum EQUATIONSOLVER_RESULT { OK, INCONSISTENT, MULTIPLE };

//Based on pseudo code from: http://en.wikipedia.org/wiki/Gaussian_elimination
template<typename T>
EQUATIONSOLVER_RESULT rowechelon(std::vector<std::vector<T> >& matrix, std::vector<T>& rhs) {
  size_t m = matrix.size();
  //for k = 1 ... m:
  for (size_t k = 0; k < m; k++)
  {
    //Find pivot for column k:
    //i_max  := argmax (i = k ... m, abs(A[i, k]))
    T max_lower_val = matrix[k][k];
    size_t max_lower_index = k;
    for (size_t i = k; i < m; i++)
    {
      if (matrix[i][k] > max_lower_val) {
        max_lower_val = matrix[i][k];
        max_lower_index = i;
      }
    }

    //if A[i_max, k] = 0 then error "Matrix is singular!"
    if (max_lower_val == 0) {
      return EQUATIONSOLVER_RESULT::INCONSISTENT;
    }

    //swap rows(k, i_max)
    if (k != max_lower_index) {
      std::swap(matrix[k], matrix[max_lower_index]);
      std::swap(rhs[k], rhs[max_lower_index]);
    }

    //Do for all rows below pivot:
    //for i = k + 1 ... m:
    for (size_t i = k + 1; i < m; i++)
    {
      //Do for all remaining elements in current row:
      //for j = k + 1 ... n:
      for (size_t j = k + 1; j < m; j++)
      {
        //A[i, j]  : = A[i, j] - A[k, j] * (A[i, k] / A[k, k])
        T factor = (matrix[i][k] / matrix[k][k]);
        matrix[i][j] -= matrix[k][j] * factor;
        rhs[i] -= rhs[k] * factor;
      }

      //Fill lower triangular matrix with zeros :
      //A[i, k]  := 0
      matrix[i][k] = 0;
    }
  }

  return EQUATIONSOLVER_RESULT::OK;
}

template<typename T>
EQUATIONSOLVER_RESULT findmultiple(std::vector<std::vector<T> >& matrix, std::vector<T>& rhs) {
  size_t m = matrix.size();
  for (size_t y1 = 0; y1 < m; y1++)
  {
    for (size_t y2 = y1 + 1; y2 < m; y2++)
    {
      T factor = 0;
      bool multiple = true;
      for (size_t x = 0; x < m; x++)
      {
        if (factor == 0) {
          if (matrix[y1][x] != 0 && matrix[y2][x] != 0) {
            factor = matrix[y1][x] / matrix[y2][x];
          }
          else if (matrix[y1][x] != 0 || matrix[y2][x] != 0) {
            multiple = false;
            break;
          }
        }
        else {
          if (matrix[y1][x] != factor*matrix[y2][x]) {
            multiple = false;
            break;
          }
        }
      }
      if (rhs[y1] != factor*rhs[y2]) {
        multiple = false;
      }

      if (multiple) {
        return EQUATIONSOLVER_RESULT::MULTIPLE;
      }
    }
  }

  return EQUATIONSOLVER_RESULT::OK;
}

template<typename T>
EQUATIONSOLVER_RESULT reducerowechelon(std::vector<std::vector<T> >& matrix, std::vector<T>& rhs) {
  size_t m = matrix.size();
  for (size_t y = 0; y < m; y++)
  {
    T factor = 0;
    for (size_t x = y; x < m; x++)
    {
      if (factor == 0 && matrix[y][x] != 0) {
        factor = matrix[y][x];
      }

      matrix[y][x] /= factor;
    }
    rhs[y] /= factor;
  }

  return EQUATIONSOLVER_RESULT::OK;
}

template<typename T>
EQUATIONSOLVER_RESULT backsubstitution(std::vector<std::vector<T> >& matrix, std::vector<T>& rhs) {
  size_t m = matrix.size();
  for (size_t y = 0; y < m; y++)
  {
    for (size_t x = y+1; x < m; x++)
    {
      rhs[y] -= matrix[y][x]*rhs[x];
    }
  }

  return EQUATIONSOLVER_RESULT::OK;
}

template<typename T>
EQUATIONSOLVER_RESULT equationsolver(std::vector<std::vector<T> >& matrix, std::vector<T>& rhs) {
  if (matrix.size() == 0 || matrix.size() != matrix[0].size()) {
    throw std::invalid_argument("Matrix must be quadratic of at least size 1");
  }

  EQUATIONSOLVER_RESULT result = findmultiple(matrix, rhs);
  if (result == MULTIPLE) {
    return EQUATIONSOLVER_RESULT::MULTIPLE;
  }
  
  result = rowechelon(matrix, rhs);

  if (result == EQUATIONSOLVER_RESULT::INCONSISTENT) {
    return EQUATIONSOLVER_RESULT::INCONSISTENT;
  }

  reducerowechelon(matrix, rhs);
  return backsubstitution(matrix, rhs);
}