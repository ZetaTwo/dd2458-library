// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <vector>
#include <cmath>

template<typename T>
class primesieve {
public:
  primesieve(size_t N) : primes(N, true), num_primes(N) {
    // 1 is not prime
    primes[0] = false;
    num_primes--;

    //Start from 2, the first prime number
    for (size_t i = 2; i <= N; i++)
    {
      //If current number is prime, tick all multiples of it
      if (primes[i-1]) {
        for (size_t j = i*i; j <= N; j += i) {
          //If this was previously considered prime, decrease counter by 1
          if (primes[j-1]) {
            num_primes--;
          }
          primes[j-1] = false;
        }
      }
    }
  }

  size_t count() const {
    return num_primes;
  }

  bool isprime(size_t i) const {
    return primes[i];
  }

private:
  std::vector<bool> primes;
  size_t num_primes;
};