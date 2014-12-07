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
T ccw(const point<T>& p1, const point<T>& p2, const point<T>& p3) {
  return (p2.getX() - p1.getX())*(p3.getY() - p1.getY()) - (p2.getY() - p1.getY())*(p3.getX() - p1.getX());
}
template<typename T>
struct ccw_sort {
  point<T> pivot;
  ccw_sort(const point<T>& p) : pivot(p) {}

  bool operator()(const point<T>& a, const point<T>& b) {
    return ccw(pivot, a, b) > 0;
  }
};

template<typename T, class Iterator>
std::vector<point<T> > convex_hull(Iterator begin, Iterator end) {
  //Create list of N+1 points
  const size_t N = end - begin;
  std::vector<point<T> > points(1);
  points.insert(points.end(), begin, end);

  //Pick point with lowest Y and place at index 1
  auto low_itr = points.begin() + 1;
  for (auto i = points.begin() + 1; i != points.end(); i++) {
    if (i->getY() < low_itr->getY()) {
      low_itr = i;
    }
    else if (i->getY() == low_itr->getY() && i->getX() < low_itr->getX()) {
      low_itr = i;
    }
  }
  std::swap(*(points.begin()+1), *low_itr);
  
  //Sort points by angle to pivot at index 1
  std::sort(points.begin() + 2, points.end(), ccw_sort<T>(points[1]));
  //Sentinel point P[0] = P[N]
  points[0] = points.back();

  size_t M = 1;
  for (size_t i = 2; i <= N; i++) {
    while (ccw(points[M - 1], points[M], points[i]) <= 0)
    {
      if (M > 1) {
        M--;
      }
      else if (M == 1) {
        break;
      }
      else {
        i++;
      }
    }
    M++;
    std::swap(points[M], points[i]);
  }
 
  points.resize(M);
  return points;
}