#include "../template.h"
/* -
name = "Numerical Integration"
[info]
description = "Simple integration of a function over an interval using Simpson's rule. Error proportional to $h^4$."
time = "$O(n)$"
- */
template<class F>
double quad(double a, double b, F f, const int n = 1000) {
  double h = (b - a) / 2 / n, v = f(a) + f(b);
  rep(i,1,n*2)
    v += f(a + i*h) * (i&1 ? 4 : 2);
  return v * h / 3;
}
