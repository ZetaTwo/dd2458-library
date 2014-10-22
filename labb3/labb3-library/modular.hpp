#include <algorithm>
#include <ostream>

#include "math.hpp"

template<typename T>
class modulo {
public:
  modulo(T value, T mod) : value(value % mod), mod(mod) {
    if (value < 0) { value += mod; }
  }
  modulo(const modulo& other) : value(other.value % other.mod), mod(other.mod) {
    if (value < 0) { value += mod; }
  }

  modulo<T> operator/(const modulo<T>& other) const {
    modulo<T> result(*this);
    result /= other;
    return result;
  }
  modulo<T> operator/(const T& factor) const {
    modulo<T> result(*this);
    result /= factor;
    return result;
  }
  friend modulo<T> operator/(const T& left, const modulo<T>& right) {
    return modulo(left, right.mod) / right;
  }
  modulo<T>& operator/=(const T& divisor) {
    *this /= modulo(divisor, mod);
    return *this;
  }
  modulo<T>& operator/=(const modulo<T>& divisor) {
    if (mod != divisor.mod) {
      throw std::invalid_argument("Operands must have same modulo");
    }

    T inv = inverse(divisor.value, mod);
    if (inv == mod) {
      throw std::invalid_argument("Right operand has no inverse");
    }

    *this *= modulo(inv, mod);

    return *this;
  }

  modulo<T> operator*(const modulo<T>& other) const {
    modulo<T> result(*this);
    result *= other;
    return result;
  }
  modulo<T> operator*(const T& factor) const {
    modulo<T> result(*this);
    result *= factor;
    return result;
  }
  friend modulo<T> operator*(const T& left, const modulo<T>& right) {
    return modulo(left, right.mod) * right;
  }
  modulo<T>& operator*=(const T& factor) {
    *this *= modulo(factor, mod);
    return *this;
  }
  modulo<T>& operator*=(const modulo<T>& other) {
    if (mod != other.mod) {
      throw std::invalid_argument("Operands must have same modulo");
    }

    if (value == 0 || other == 0) {
      value = 0;
      return *this;
    }

    T q = mod / value;
    T r = mod % value;

    T p1 = value * (other.value % q);
    T p2 = r * (other.value / q);

    if (p1 > p2) {
      value = p1 - p2;
    }
    else {
      value = mod - (p2 - p1);
    }

    return *this;
  }
  

  modulo<T> operator+(const T& term) const {
    modulo<T> result(*this);
    result += term;
    return result;
  }
  modulo<T> operator+(const modulo<T>& other) const {
    modulo result(*this);
    result += other;
    return result;
  }
  friend modulo<T> operator+(const T& left, const modulo<T>& right) {
    return modulo(left, right.mod) + right;
  }
  modulo<T>& operator+=(const T& term) {
    *this += modulo(term, mod);
    return *this;
  }
  modulo<T>& operator+=(const modulo<T>& other) {
    if (mod != other.mod) {
      throw std::invalid_argument("Operands must have same modulo");
    }

    T larger = std::max(value, other.value);
    T smaller = std::min(value, other.value);
    T left = mod - larger;
    if (smaller < left) {
      value = smaller + larger;
    }
    else {
      value = smaller - left;
    }

    return *this;
  }

  modulo<T> operator-(const modulo<T>& other) const {
    modulo<T> result(*this);
    result -= other;
    return result;
  }
  modulo<T> operator-(const T& term) const {
    modulo<T> result(*this);
    result -= term;
    return result;
  }
  friend modulo<T> operator-(const T& left, const modulo<T>& right) {
    return modulo(left, right.mod) - right;
  }
  modulo<T>& operator-=(const T& term) {
    *this -= modulo(term, mod);
    return *this;
  }
  modulo<T>& operator-=(const modulo<T>& other) {
    if (mod != other.mod) {
      throw std::invalid_argument("Operands must have same modulo");
    }

    if (other.value < value) {
      value -= other.value;
    }
    else {
      T diff = other.value - value;
      value = mod - diff;
    }

    return *this;
  }
  
  modulo<T>& operator=(const modulo<T>& other) {
    value = other.value;
    mod = other.mod;

    return *this;
  }

  bool operator==(const modulo<T>& other) const {
    return value == other.value && mod == other.mod;
  }
  bool operator!=(const modulo<T>& other) const {
    return !(*this == other);
  }
  bool operator==(const T& other) const {
    return *this == modulo(other, mod);
  }
  bool operator!=(const T& other) const {
    return *this != modulo(other, mod);
  }
  friend bool operator==(const T& left, const modulo<T>& right) {
    return right == left;
  }
  friend bool operator!=(const T& left, const modulo<T>& right) {
    return right != left;
  }

  friend std::ostream& operator<<(std::ostream& stream, const modulo<T>& value) {
    return stream << value.value;
  }

private:
  T mod;
  T value;
};