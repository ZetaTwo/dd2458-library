// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

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