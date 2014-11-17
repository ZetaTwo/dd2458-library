// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <vector>

template<typename T>
class primesieve {
public:
  primesieve(size_t N) : primesstatus(N, true), num_primes(N) {
    // 1 is not prime
    primesstatus[0] = false;
    num_primes--;

    //Start from 2, the first prime number
    for (size_t i = 2; i <= N; i++)
    {
      //If current number is prime, tick all multiples of it
      if (primesstatus[i - 1]) {
        for (size_t j = i*i; j <= N; j += i) {
          //If this was previously considered prime, decrease counter by 1
          if (primesstatus[j - 1]) {
            num_primes--;
          }
          primesstatus[j - 1] = false;
        }
      }
    }

    for (size_t i = 0; i < primesstatus.size(); i++) {
      if (primesstatus[i]) {
        primes.push_back(i + 1);
      }
    }
  }

  size_t count() const {
    return num_primes;
  }

  bool isprime(size_t i) const {
    return primesstatus[i];
  }

  const std::vector<T>& getPrimes() const {
    return primes;
  }

private:
  std::vector<bool> primesstatus;
  std::vector<T> primes;
  size_t num_primes;
};