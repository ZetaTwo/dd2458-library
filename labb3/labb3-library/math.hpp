// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <stdexcept>
#include <vector>
#include <bitset>
#include <limits>
#include <map>
#include <algorithm>

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

//Calculates base^exponent (mod modulus)
template<typename T>
T pow_mod(T base, T exponent, T modulus)
{
  T result = 1;
  while (exponent > 0)
  {
    if (exponent % 2 == 1)
      result = (result * base) % modulus;
    exponent = exponent >> 1;
    base = (base * base) % modulus;
  }
  return result;
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

//Solves a system of congruences x = a_i (mod m_i) even when m_i are not pairwise-coprime.
template<typename T>
T generalchineseremainder(std::vector<T> remainders, std::vector<T> moduli) {
  if (remainders.size() != moduli.size()) {
    throw std::invalid_argument("Size of remainders and moduli must be equal");
  }

  if (remainders.size() == 0) {
    return 0;
  }

  if (remainders.size() == 1) {
    return remainders[0];
  }

  if (moduli[0] != moduli[1]) {
    //Method of successive substitution
    //http://en.wikipedia.org/wiki/Method_of_successive_substitution
    if (remainders[1] > remainders[0]) {
      std::swap(remainders[0], remainders[1]);
      std::swap(moduli[0], moduli[1]);
    }

    T left = moduli[1];
    T right = (remainders[0] - remainders[1]) % moduli[0];
    T mod = moduli[0];

    T g = gcd(left, gcd(right, mod));
    left /= g;
    right /= g;
    mod /= g;

    T inv = inverse(left, mod);
    if (inv == mod) {
      return -1;
    }

    left = (left * inv) % mod;
    right = (right * inv) % mod;

    T pair_rem = remainders[1] + moduli[1] * right;
    T pair_mod = moduli[1] * mod;

    remainders.push_back(pair_rem);
    moduli.push_back(pair_mod);
  }
  else {
    if (remainders[0] != remainders[1]) {
      return -1;
    }
    else {
      remainders.push_back(remainders[0]);
      moduli.push_back(moduli[0]);
    }
  }

  remainders.erase(remainders.begin(), remainders.begin() + 2);
  moduli.erase(moduli.begin(), moduli.begin() + 2);

  return generalchineseremainder(remainders, moduli);
  
}