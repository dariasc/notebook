#include "../template.h"
#include "euclid.h"
/* -
name = "Chinese Remainder Theorem"
[info]
description = "Computes $x$ such that $x equiv a space (mod m)$, $x equiv b space (mod n)$. If $|a| < m$ and $|b| < n$, $x$ will obey $0 <= x < lcm(m, n)$. Assumes $m n < 2^62$."
time = "$O(log n)$"
- */
ll crt(ll a, ll m, ll b, ll n) {
  if (n > m) swap(a, b), swap(m, n);
  ll x, y, g = euclid(m, n, x, y);
  assert((a - b) % g == 0); // else no solution
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m*n/g : x;
}
