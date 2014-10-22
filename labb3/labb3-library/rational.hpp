#include <cmath>

#include "math.hpp"

template<typename T>
class rational {
public:
  rational() : numerator(0), denominator(1) {}
  rational(const rational& other) : numerator(other.numerator), denominator(other.denominator) {}
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
  rational<T>& operator/=(const T& divisor) {
    rational<T> div(divisor, 1);
    *this /= divisor;

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

  rational<T> operator+(const rational<T>& other) const {
    rational<T> result(*this);
    result += other;
    return result;
  }
  rational<T> operator-(const rational<T>& other) const {
    rational<T> result(*this);
    result += (-1)*other;
    return result;
  }
  rational<T>& operator+=(const rational<T>& other) {
    if (denominator == 0 || other.denominator == 0) {
      return *this;
    }

    T temp_numerator = (numerator*other.denominator + other.numerator*denominator) / gcd(denominator, other.denominator);
    T temp_denominator = lcm(denominator, other.denominator);
    numerator = temp_numerator;
    denominator = temp_denominator;

    return *this;
  }
  rational<T>& operator-=(const rational<T>& other) {
    *this += other*(-1);

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
  bool operator!=(const rational<T>& other) const {
    return !(*this == other);
  }

  T getNumerator() const {
    return numerator;
  }

  T getDenominator() const {
    return denominator;
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