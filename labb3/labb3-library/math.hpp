
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