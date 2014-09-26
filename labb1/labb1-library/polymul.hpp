#include <vector>
#include <algorithm>

template<typename T, class iterator_type_input, class iterator_type_result>
void low_high_sum(size_t mid_size, iterator_type_input poly_begin, iterator_type_input low, iterator_type_input poly_end, iterator_type_result result)
{
  iterator_type_input high_itr = low;
  iterator_type_input low_itr = poly_begin;

  while (low_itr != low || high_itr != poly_end)
  {
    if (low_itr != low) {
      *result += *low_itr;
      low_itr++;
    }

    if (high_itr != poly_end) {
      *result += *high_itr;
      high_itr++;
    }
    result++;
  }
}

template<typename T, class iterator_type_input1, class iterator_type_input2, class iterator_type_result>
void polymul(iterator_type_input1 poly1_begin, iterator_type_input1 poly1_end,
  iterator_type_input2 poly2_begin, iterator_type_input2 poly2_end,
  iterator_type_result result) {

  size_t poly1_size = poly1_end - poly1_begin;
  size_t poly2_size = poly2_end - poly2_begin;
  size_t result_size = poly1_size + poly2_size - 2;

  if (poly1_size == 0 || poly2_size == 0) {
    *result = 0;
    return;
  }

  if (poly1_size == 1 && poly2_size == 1) {
    *result = (*poly1_begin) * (*poly2_begin);
    return;
  }

  size_t max_size = std::max(poly1_size, poly2_size);
  size_t mid_size = 1 + ((max_size - 1) / 2); //mid_size = ceil(max_size/2)

  size_t z_size = std::max<size_t>(1, 2 * mid_size);
  std::vector<T> z0(z_size), z1(z_size), z2(z_size);

  iterator_type_input1 low1 = poly1_begin + std::min(mid_size, poly1_size);
  iterator_type_input2 low2 = poly2_begin + std::min(mid_size, poly2_size);

  polymul<T>(poly1_begin, low1, poly2_begin, low2, z0.begin()); // (low1 * low2)
  polymul<T>(low1, poly1_end, low2, poly2_end, z2.begin()); // (high1 * high2)

  // (high1 + low1) * (high2 + low2)
  vector<T> highlow1(mid_size), highlow2(mid_size);
  low_high_sum<T>(mid_size, poly1_begin, low1, poly1_end, highlow1.begin());
  low_high_sum<T>(mid_size, poly2_begin, low2, poly2_end, highlow2.begin());
  polymul<T>(highlow1.cbegin(), highlow1.cend(), highlow2.cbegin(), highlow2.cend(), z1.begin());

  // (z2*10^(2*m2))+((z1-z2-z0)*10^(m2))+(z0)
  size_t pos = 0;
  typename vector<T>::const_iterator z0itr = z0.cbegin(), z1itr = z1.cbegin(), z2itr = z2.cbegin(), z0itr2 = z0.cbegin(), z2itr2 = z2.cbegin();
  while (pos <= result_size && (z0itr != z0.end() || z1itr != z1.end() || z2itr != z2.end() || z0itr2 != z0.end() || z2itr2 != z2.end()))
  {
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

    *result++ = val;
    pos++;
  }

  return;
}