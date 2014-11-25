// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <cmath>
#include <initializer_list>
#include <utility>
#include <iostream>

template<typename T>
class point {
public:
  point() : x(T{}), y(T{}) {}
  point(const T& a, const T& b) : x(a), y(b) {}
  point(const point& other) : x(other.x), y(other.y) {}
  point(const std::pair<T, T>& pair) : x(pair.first), y(pair.second) {}
  point(const point&& other) : x(other.x), y(other.y) {}
  point(const initializer_list<T>& list) : x(list[0]), y(list[1]) {}

  point& operator=(const point& other) { x = other.x; y = other.y; return *this; }
  point& operator=(const initializer_list<T>& list) { x = list[0]; y = list[1]; return *this; }
  point& operator=(const std::pair<T, T>& pair) { x = pair.first; y = pair.second; return *this; }

  point& operator*=(const T& coeff) { x *= coeff; y *= coeff; return *this; }
  point operator*(const T& coeff) const { point res(*this); res *= coeff; return res; }

  point& operator/=(const T& coeff) { x /= coeff; y /= coeff; return *this; }
  point operator/(const T& coeff) const { point res(*this); res /= coeff; return res; }

  point& operator+=(const T& term) { x += term; y += term; return *this; }
  point operator+(const T& term) const { point res(*this); res += term; return res; }
  point& operator+=(const point& other) { x += other.x; y += other.y; return *this; }
  point operator+(const point& other) const { point res(*this); res += other; return res; }

  point operator-() const { point res(*this); res.x *= -1; res.y *= -1; return res; }

  point& operator-=(const T& term) { *this += (-term); return *this; }
  point operator-(const T& term) const { point res(*this); res -= term; return res; }
  point& operator-=(const point& other) { *this += (-other); return *this; }
  point operator-(const point& other) const { point res(*this); res -= other; return res; }

  template<typename F>
  static F norm(const point& p) { return sqrt(p.x*p.x + p.y*p.y); }
  template<typename F>
  F norm() const { return norm(*this); }

  template<typename F>
  static F norm2(const point& p) { return p.x*p.x + p.y*p.y; }
  template<typename F>
  F norm2() const { return norm(*this); }

  template<typename F>
  static F dist(const point& a, const point& b) { return norm(a - b); }
  template<typename F>
  F dist(const point& other) const { return norm(*this - other); }

  static T inner_product(const point& a, const point& b) { return a.x * b.x + a.y * b.y; }
  T inner_product(const point& other) { return inner_product(*this, other); }

  static T cross_product(const point& a, const point& b) { return a.x * b.y - a.y * b.x; }
  T cross_product(const point& other) { return cross_product(*this, other); }

  template<typename F>
  static F angle_between(const point& a, const point& b) { return acos(inner_product(a, b) / (norm(a) * norm(b))); }
  template<typename F>
  F angle_between(const point& other) const { return angle_between(*this, other); }

  const T& getX() const { return x; }
  const T& getY() const { return y; }

  friend istream& operator>> (istream &input, point& p) {
    input >> p.x >> p.y;
    return input;
  }

  friend ostream& operator<< (ostream &output, point& p) {
    output << "(" << p.x << "," << p.y << ")";
    return output;
  }

private:
  T x;
  T y;
};

//TODO: Not working
//Functor to sort points in clockwise order
//Use with std::sort(container<point>::iterator, container<point>::iterator, clockwise_sort_func(container<point>::iterator, container<point>::iterator));
/*template<typename T>
struct clockwise_sort_func {
public:
  template<class Iterator>
  clockwise_sort_func(Iterator begin, Iterator end) {
    size_t n = end - begin;
    for (Iterator p = begin; p != end; p++) {
      center += *p / n;
    }
  }

  bool operator()(const point<T>& a, const point<T>& b) const
  {
    if (a.getX() - center.getX() >= 0 && b.getX() - center.getX() < 0) {
      return true;
    }
    else if (a.getX() - center.getX() < 0 && b.getX() - center.getX() >= 0) {
      return false;
    }
    else if (a.getX() - center.getX() == 0 && b.getX() - center.getX() == 0) {
      if (a.getY() - center.getY() >= 0 || b.getY() - center.getY() >= 0) {
        return a.getY() > b.getY();
      }
      return b.getY() > a.getY();
    }

    // compute the cross product of vectors (center -> a) x (center -> b)
    int det = point<T>::cross_product(center - a, center - b);
    //int det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);
    if (det < 0) {
      return true;
    }
    else if (det > 0) {
      return false;
    }

    // points a and b are on the same line from the center
    // check which point is closer to the center
    //int d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
    double d1 = point<T>::norm2<double>(a - center);
    //int d2 = (b.x - center.x) * (b.x - center.x) + (b.y - center.y) * (b.y - center.y);
    double d2 = point<T>::norm2<double>(b - center);
    return d1 > d2;
  }
private:
  point<T> center;
};*/

template<typename F, class Iterator>
F polygon_area(Iterator begin, Iterator end) {

  F res = F{};
  Iterator last = begin, i = last + 1;
  for (; i != end; last = i++) {
    res -= last->getX()*i->getY();
    res += last->getY()*i->getX();
  }
  res -= last->getX()*begin->getY();
  res += last->getY()*begin->getX();

  return res/2;
}

template<typename T, class Iterator>
int inside_poly(const point<T>& p, Iterator begin, Iterator end)
{
  Iterator i, j;
  //Check if on boundary
  for (i = begin, j = end - 1; i != end; j = i++) {
    T cross = point<T>::cross_product((*i - *j), (p - *j));
    if (cross == 0) {
      return 1;
    }
  }

  //Check if inside or outside
  int c = 0;
  for (i = begin, j = end - 1; i != end; j = i++) {
    if (((i->getY() > p.getY()) != (j->getY() > p.getY())) &&
      (p.getX() < (j->getX() - i->getX()) * static_cast<double>((p.getY() - i->getY())) / (j->getY() - i->getY()) + i->getX()))
      c = 2-c;
  }

  return c;
}