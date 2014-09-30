// Polynomial multiplication algorithm
// Based on: http://en.wikipedia.org/wiki/Karatsuba_algorithm
// -----------------------------------------
// Authors: Magnus Olsson  (magolsso@kth.se)
//          Calle Svensson (carlsven@kth.se)

#include <vector>
#include <algorithm>

namespace polymul {

  //Calculates the (low+high) vector in the polymul algorithm
  //This function is used internally in the algorithm and should not be called directly
  template<typename T>
  void low_high_sum(std::vector<T>& low, std::vector<T>& high)
  {
    for (typename std::vector<T>::iterator low_itr = low.begin(), high_itr = high.begin(); high_itr != high.end(); high_itr++, low_itr++)
    {
      *low_itr += *high_itr;
    }
  }

  //Naive quadratic polynomial multiplication.
  //Used for polynomials of small size where the n^(log2(3)) algorithm has too much overhead.
  //This function is used internally in the algorithm and should not be called directly
  template<typename T>
  std::vector<T> polymul_quad(const std::vector<T>& polynomial1, const std::vector<T>& polynomial2) {
    std::vector<T> result(polynomial1.size() + polynomial2.size() - 1, 0);

    for (size_t i = 0; i < polynomial1.size(); i++)
    {
      for (size_t j = 0; j < polynomial2.size(); j++)
      {
        result[i + j] += polynomial1[i] * polynomial2[j];
      }
    }

    return result;
  }

  //Algorithm for multiplying two polynomials. O(n^log2(3))
  //polynomial1 and polynomial2 are two vector<T> containing the coefficients of type T of the two polynomials
  //The function returns a vector<T> containing the coefficients of type T of the product of polynomial1 and polynomial2
  //All coefficients are in increasing magnitude order, i.e. a0 + a1*x + a2*x^2 ...
  template<typename T>
  std::vector<T> polymul(const std::vector<T>& polynomial1, const std::vector<T>& polynomial2) {
    typedef typename std::vector<T>::iterator poly_iterator;

    if (polynomial1.size() <= 128 || polynomial2.size() <= 128) {
      return polymul_quad(polynomial1, polynomial2);
    }

    size_t max_size = std::max(polynomial1.size(), polynomial2.size());
    size_t mid_size = 1 + ((max_size - 1) / 2); //mid_size = ceil(max_size/2)

    std::vector<T> low1(polynomial1.begin(), polynomial1.begin() + std::min(mid_size, polynomial1.size()));
    std::vector<T> low2(polynomial2.begin(), polynomial2.begin() + std::min(mid_size, polynomial2.size()));
    std::vector<T> high1(polynomial1.begin() + std::min(mid_size, polynomial1.size()), polynomial1.end());
    std::vector<T> high2(polynomial2.begin() + std::min(mid_size, polynomial2.size()), polynomial2.end());

    std::vector<T> z0 = polymul<T>(low1, low2); // (low1 * low2)
    std::vector<T> z2 = polymul<T>(high1, high2); // (high1 * high2)

    // (high1 + low1) * (high2 + low2)
    low_high_sum(low1, high1);
    low_high_sum(low2, high2);
    std::vector<T> z1 = polymul<T>(low1, low2);

    // (z2*10^(2*m2))+((z1-z2-z0)*10^(m2))+(z0)
    size_t pos = 0;
    typename vector<T>::const_iterator z0itr = z0.cbegin(), z1itr = z1.cbegin(), z2itr = z2.cbegin(), z0itr2 = z0.cbegin(), z2itr2 = z2.cbegin();
    std::vector<T> result(polynomial1.size() + polynomial2.size() - 1);
    for (poly_iterator res = result.begin(); res != result.end(); res++) {
      T val = T();

      // +z0
      if (z0itr != z0.end()) {
        val += *z0itr;
        z0itr++;
      }

      // +(z1-z2-z0) <- m2
      if (pos >= mid_size) {
        if (z1itr != z1.end()) {
          val += *z1itr;
          z1itr++;
        }
        if (z2itr2 != z2.end()) {
          val -= *z2itr2;
          z2itr2++;
        }
        if (z0itr2 != z0.end()) {
          val -= *z0itr2;
          z0itr2++;
        }
      }

      // +z2 <- 2*m2
      if (pos >= 2 * mid_size && z2itr != z2.end()) {
        val += *z2itr;
        z2itr++;
      }

      *res = val;
      pos++;
    }

    return result;
  }

}