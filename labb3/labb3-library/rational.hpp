// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <cmath>

#include "math.hpp"

template<typename T>
class rational {
public:
  rational() : numerator(0), denominator(1) {}
  rational(const rational& other) : numerator(other.numerator), denominator(other.denominator) {}
  explicit rational(T numerator) : numerator(numerator), denominator(1) {};
  rational(T numerator, T denominator) : numerator(numerator), denominator(denominator) {
    normalize();
  }

  rational<T> operator/(const rational<T>& other) const {
    rational<T> result(*this);
    result /= other;
    return result;
  }
  rational<T> operator/(const T& factor) const {
    rational<T> result(*this);
    result /= factor;
    return result;
  }
  friend rational<T> operator/(const T& left, const rational<T>& right) {
    return rational(left) / right;
  }
  rational<T>& operator/=(const T& divisor) {
    *this /= rational(divisor);
    return *this;
  }
  rational<T>& operator/=(const rational<T>& divisor) {
    numerator *= divisor.denominator;
    denominator *= divisor.numerator;
    normalize();

    return *this;
  }

  rational<T> operator*(const rational<T>& other) const {
    rational<T> result(*this);
    result *= other;
    return result;
  }
  rational<T> operator*(const T& factor) const {
    rational<T> result(*this);
    result *= factor;
    return result;
  }
  friend rational<T> operator*(const T& left, const rational<T>& right) {
    return rational(left) * right;
  }
  rational<T>& operator*=(const rational<T>& other) {
    numerator *= other.numerator;
    denominator *= other.denominator;
    normalize();

    return *this;
  }
  rational<T>& operator*=(const T& factor) {
    numerator *= factor;
    normalize();

    return *this;
  }

  rational<T> operator+(const T& term) const {
    rational<T> result(*this);
    result += term;
    return result;
  }
  rational<T> operator+(const rational<T>& other) const {
    rational<T> result(*this);
    result += other;
    return result;
  }
  friend rational<T> operator+(const T& left, const rational<T>& right) {
    return rational(left) + right;
  }
  rational<T>& operator+=(const T& term) {
     *this += rational(term);
     return *this;
  }
  rational<T>& operator+=(const rational<T>& other) {
    if (denominator == 0 || other.denominator == 0) {
      return *this;
    }

    T g = gcd(denominator, other.denominator);
    T temp_numerator = (numerator*other.denominator) / g + (other.numerator*denominator) / g;
    T temp_denominator = lcm(denominator, other.denominator);

    numerator = temp_numerator;
    denominator = temp_denominator;
    normalize();

    return *this;
  }

  rational<T> operator-(const rational<T>& other) const {
    rational<T> result(*this);
    result += (-1)*other;
    return result;
  }
  rational<T> operator-(const T& term) const {
    rational<T> result(*this);
    result += (-1)*term;
    return result;
  }
  friend rational<T> operator-(const T& left, const rational<T>& right) {
    return rational(left) - right;
  }
  rational<T>& operator-=(const rational<T>& other) {
    *this += other*(-1);
    return *this;
  }
  rational<T>& operator-=(const T& term) {
    *this += rational(term)*(-1);
    return *this;
  }
  
  rational<T>& operator=(const rational<T>& other) {
    numerator = other.numerator;
    denominator = other.denominator;

    return *this;
  }
  bool operator==(const rational<T>& other) const {
    return (numerator == other.numerator) && (denominator == other.denominator);
  }
  bool operator==(const T& other) const {
    return *this == rational<T>(other);
  }
  bool operator!=(const rational<T>& other) const {
    return !(*this == other);
  }
  bool operator!=(const T& other) const {
    return !(*this == other);
  }
  friend bool operator==(const T& left, const rational<T>& right) {
    return right == left;
  }
  friend bool operator!=(const T& left, const rational<T>& right) {
    return right != left;
  }

  T getNumerator() const {
    return numerator;
  }
  T getDenominator() const {
    return denominator;
  }
  double getFraction() const {
    return static_cast<double>(numerator) / denominator;
  }

private:
  void normalize() {
    if (denominator == 0) {
      numerator = 0;
      return;
    }

    if (denominator < 0) {
      numerator *= -1;
      denominator *= -1;
    }
    T g = gcd(abs(numerator), denominator);
    numerator /= g;
    denominator /= g;
  }

  T numerator;
  T denominator;
};