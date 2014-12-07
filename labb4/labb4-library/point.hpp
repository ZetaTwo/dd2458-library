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
  point(const std::initializer_list<T>& list) : x(list[0]), y(list[1]) {}

  point& operator=(const point& other) { x = other.x; y = other.y; return *this; }
  point& operator=(const point&& other) { x = other.x; y = other.y; return *this; }
  point& operator=(const std::initializer_list<T>& list) { x = list[0]; y = list[1]; return *this; }
  point& operator=(const std::pair<T, T>& pair) { x = pair.first; y = pair.second; return *this; }

  bool operator==(const point& other) const { return x==other.x && y==other.y; }

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
  static F norm(const point& p) { return sqrt(norm2(p)); }
  template<typename F>
  F norm() const { return norm(*this); }

  static T norm2(const point& p) { return p.x*p.x + p.y*p.y; }
  T norm2() const { return norm2(*this); }

  template<typename F>
  static F dist(const point& a, const point& b) { return norm(a - b); }
  template<typename F>
  F dist(const point& other) const { return norm(*this - other); }

  static T inner_product(const point& a, const point& b) { return a.x * b.x + a.y * b.y; }
  T inner_product(const point& other) { return inner_product(*this, other); }

  static T cross_product(const point& a, const point& b) { return a.x * b.y - a.y * b.x; }
  static T cross_product(const point& o, const point& a, const point& b) { return cross_product(a-o, b-o); }
  T cross_product(const point& other) { return cross_product(*this, other); }

  template<typename F>
  static F angle_between(const point& a, const point& b) { return acos(inner_product(a, b) / (norm(a) * norm(b))); }
  template<typename F>
  F angle_between(const point& other) const { return angle_between(*this, other); }

  const T& getX() const { return x; }
  const T& getY() const { return y; }

  friend std::istream& operator>> (std::istream &input, point& p) {
    input >> p.x >> p.y;
    return input;
  }

  friend std::ostream& operator<< (std::ostream &output, point& p) {
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

template<typename T>
bool on(const point<T>& p, const point<T>& a, const point<T>& b) {

  if (p == a || p == b) {
    return true;
  }

  point<T> d1 = b - a;
  point<T> d2 = p - a;
  T cross = point<T>::cross_product(d1, d2);

  if (cross != 0) {
    return false;
  }

  T dot = d1.inner_product(d2);
  return dot > 0 && dot < d1.norm2();
}

template<typename T, class Iterator>
int inside_poly(const point<T>& p, Iterator begin, Iterator end)
{
  Iterator i, j;
  //Check if on boundary
  for (i = begin, j = end - 1; i != end; j = i++) {
    if (on(p, *i, *j)) {
      return 0;
    }
  }

  //Check if inside or outside
  int c = -1;
  for (i = begin, j = end - 1; i != end; j = i++) {
    if (
      ((i->getY() > p.getY()) != (j->getY() > p.getY())) &&
      (p.getX() < (j->getX() - i->getX()) * static_cast<double>(p.getY() - i->getY()) / (j->getY() - i->getY()) + i->getX())
      ) {
      c *= -1;
    }
  }

  return c;
}

template<typename T>
struct PointSortLexicographically {
  bool operator ()(const point<T> &a, const point<T> &b) const {
    return a.getX() < b.getX() || (a.getX() == b.getX() && a.getY() < b.getY());
  }
};

template<typename T, class Iterator>
std::vector<point<T> > convex_hull(Iterator begin, Iterator end) {
  //Create list of N+1 points
  const size_t n = end - begin;
  int k = 0;
  vector<point<T> > P(begin, end);
  vector<point<T> > H(2 * n);

  // Sort points lexicographically
  sort(P.begin(), P.end(), PointSortLexicographically<T>());

  // Build lower hull
  for (int i = 0; i < n; ++i) {
    while (k >= 2 && point<T>::cross_product(H[k - 2], H[k - 1], P[i]) <= 0) {
      k--;
    }
    H[k++] = P[i];
  }

  // Build upper hull
  for (int i = n - 2, t = k + 1; i >= 0; i--) {
    while (k >= t && point<T>::cross_product(H[k - 2], H[k - 1], P[i]) <= 0) {
      k--;
    }
    H[k++] = P[i];
  }

  if (k == 3 && H[0] == H[1]) k--;
  H.resize(std::max(1, k-1));
  return H;
}