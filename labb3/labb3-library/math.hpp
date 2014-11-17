// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <vector>
#include <bitset>
#include <limits>
#include <map>
#include <algorithm>

#include "primesieve.hpp"

//Calculates GCD(a, b)
template<typename T>
T gcd(T a, T b) {
  T t;
  while (b != 0) {
    t = b;
    b = a % b;
    a = t;
  }

  return a;
}

//Calculates GCD(a1, a2, a3, ...)
template<typename T>
T gcd(const std::vector<T>& numbers) {
  auto n = numbers.begin();
  T res = *n++;
  while (n != numbers.end()) {
    res = gcd(res, *n++);
  }
  
  return res;
}

//Calculates LCM(a, b)
template<typename T>
T lcm(T a, T b) {
  T g = gcd(a, b);
  return (a / g) * b;
}

//Stores result of an extended Euclidean algorithm calculation
template<typename T>
struct egcd_res {
  T coeff_a;
  T coeff_b;
  T gcd;
  T quotient_a;
  T quotient_b;
};

//Extended Euclidean algorithm
template<typename T>
egcd_res<T> egcd(T a, T b) {
  egcd_res<T> res = { 1, 0, a, 1, 0 };
  T r = b;
  T temp;

  while (r != 0) {
    //quotient = old_r / r
    T quotient = res.gcd / r;

    //(old_r, r) := (r, old_r - quotient * r)
    temp = res.gcd - quotient*r;
    res.gcd = r;
    r = temp;

    //(old_s, s) := (s, old_s - quotient * s)
    temp = res.coeff_a - quotient * res.quotient_b;
    res.coeff_a = res.quotient_b;
    res.quotient_b = temp;

    //(old_t, t) := (t, old_t - quotient * t) 
    temp = res.coeff_b - quotient * res.quotient_a;
    res.coeff_b = res.quotient_a;
    res.quotient_a = temp;
  }

  return res;
}

//Returns the inverse of a modulo n or n if there is no inverse
template<typename T>
T inverse(T a, T n) {
  T t = 0;
  T newt = 1;
  T r = n;
  T newr = a;
  while (newr != 0) {
    //quotient := r div newr
    T quotient = r / newr;

    //(t, newt) := (newt, t - quotient * newt)
    T temp = t - quotient * newt;
    t = newt;
    newt = temp;

    //(r, newr) := (newr, r - quotient * newr)
    temp = r - quotient * newr;
    r = newr;
    newr = temp;
  }

  if (r > 1) {
    return n;
  }
  if (t < 0) {
    t += n;
  }
  return t;

}

//Multiplies two numbers a and b reduced by a modulo avoiding overflow.
template<typename T>
T mulmod(T a, T b, T mod) {
  // Based on: http://en.wikipedia.org/wiki/Kochanski_multiplication
  std::bitset<sizeof(T)*std::numeric_limits<unsigned char>::digits> mult(b);
  T res = 0;
  for (size_t i = mult.size(); i--;) {
    res <<= 1;
    res %= mod;
    if (mult.test(i)) {
      res += a;
    }
    res %= mod;
  }
  return res;
}

//Solves a system of congruences x = a_i (mod m_i)
template<typename T>
T chineseremainder(const std::vector<T>& remainders, const std::vector<T>& moduli) {
  T N = 1;
  for (auto& v : moduli) N *= v;

  T x = 0;
  for (auto ai = remainders.begin(), ni = moduli.begin(); ai != remainders.end() && ni != moduli.end(); ai++, ni++)
  {
    if (*ai > 0) {
      T Nni = N / (*ni);
      T term = mulmod(*ai, Nni, N);
      term = mulmod(term, inverse(Nni, *ni), N);
      x += term;
    }
  }

  return x % N;
}

//Shorthand for solving a congruence when N=2
template<typename T>
T chineseremainder(const T& a, const T& m, const T& b, const T& n) {
  return chineseremainder(std::vector<T>({ a, b }), std::vector<T>({ m, n }));
}

template<typename T>
T generalchineseremainder(std::vector<T> remainders, std::vector<T> moduli) {
  T max_mod = *max_element(moduli.begin(), moduli.end());
  primesieve<T> primes(static_cast<T>(ceil(sqrt(max_mod))));

  //TODO: This check only works for N=2
  if (abs((remainders[1] - remainders[0]) % gcd(moduli[1], moduli[0])) != 0) {
    return -1;
  }

  //Base case
  if (gcd(moduli) == 1) {
    return chineseremainder(remainders, moduli);
  }

  //Find prime divisor
  std::map<T, T> system;
  for (auto prime : primes.getPrimes()) {

    //Break up into parts
    for (size_t i = 0; i < remainders.size(); i++) {
      //Calculate largest prime exponent
      T pexp = prime;
      while (moduli[i] % pexp == 0) { pexp *= prime; }
      pexp /= prime;
      if (pexp == 1) continue;

      //Add split
      const T& m = pexp;
      const T& a = remainders[i] % m;
      auto entry = system.find(m);
      if (entry != system.end() && entry->second != a) {
        return -1;
      }
      else {
        system[m] = a;
      }
      moduli[i] /= pexp;
    }
  }

  for (size_t i = 0; i < moduli.size(); i++) {
    if (moduli[i] != 1) {
      system[moduli[i]] = remainders[i];
    }
  }

  //Convert map to vectors
  std::vector<T> remainders2, moduli2;
  for (auto pair : system) {
    moduli2.push_back(pair.first);
    remainders2.push_back(pair.second);
  }

  //Clean
  for (size_t i = 0; i < moduli2.size(); i++) {
    for (size_t j = 0; j < moduli2.size();) {
      if (i != j && moduli2[j] % moduli2[i] == 0) {
        moduli2.erase(moduli2.begin() + i);
        remainders2.erase(remainders2.begin() + i);
      }
      else {
        j++;
      }
    }
  }


  //Calculate
  if (remainders2.size() == 1) {
    return remainders2[0];
  }
  else {
    return generalchineseremainder(remainders2, moduli2);
  }
}