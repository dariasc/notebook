#include "../template.h"
/* -
name = "Integer Determinant"
[info]
description = "Calculates determinant using modular arithmetics. Can be used for pure-integer version by removing modulo operations."
time = "$O(N^3)$"
- */
ll det(vec<vec<ll>>& a) {
  int n = sz(a); ll ans = 1;
  rep(i,0,n) {
    rep(j,i+1,n) {
      while (a[j][i] != 0) { // gcd step
        ll t = a[i][i] / a[j][i];
        if (t) rep(k,i,n)
          a[i][k] = (a[i][k] - a[j][k] * t) % mod;
        swap(a[i], a[j]);
        ans *= -1;
      }
    }
    ans = ans * a[i][i] % mod;
    if (!ans) return 0;
  }
  return (ans + mod) % mod;
}
