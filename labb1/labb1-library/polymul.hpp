#include <vector>
#include <algorithm>

template<typename T>
inline std::vector<T> low_high_sum(std::vector<T> low, std::vector<T> high)
{
  std::vector<T> result(std::max(low.size(), high.size()));

  for (std::vector<T>::iterator itr = result.begin(), low_itr = low.begin(), high_itr = high.begin(); itr != result.end(); itr++)
  {
    if (low_itr != low.end()) {
      *itr += *low_itr;
      low_itr++;
    }

    if (high_itr != high.end()) {
      *itr += *high_itr;
      high_itr++;
    }
  }

  return result;
}

template<typename T>
std::vector<T> polymul(const std::vector<T>& polynomial1, const std::vector<T>& polynomial2) {
  typedef std::vector<T>::iterator poly_iterator;

  if (polynomial1.size() == 0 || polynomial2.size() == 0) {
     return std::vector<T>(1, 0);
  }

  if (polynomial1.size() == 1) {
    std::vector<T> result(polynomial2);
    for (poly_iterator itr = result.begin(); itr != result.end(); itr++)
    {
      *itr *= polynomial1.front();
    }
    return result;
  }

  if (polynomial2.size() == 1) {
    std::vector<T> result(polynomial1);
    for (poly_iterator itr = result.begin(); itr != result.end(); itr++)
    {
      *itr *= polynomial2.front();
    }
    return result;
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
  std::vector<T> highlow1 = low_high_sum(low1, high1);
  std::vector<T> highlow2 = low_high_sum<T>(low2, high2);
  std::vector<T> z1 = polymul<T>(highlow1, highlow2);

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
    if (pos >= 2*mid_size && z2itr != z2.end()) {
      val += *z2itr;
      z2itr++;
    }

    *res = val;
    pos++;
  }

  return result;
}