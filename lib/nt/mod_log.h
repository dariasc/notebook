#include "../template.h"
/* -
name = "Modular Logarithm"
[info]
description = "Returns the smallest $x > 0$ such that $a^x = b space (mod m)$, or $-1$ if no such $x$ exists. Uses baby-step giant-step method."
time = "$O(sqrt(m))$"
- */
ll modLog(ll a, ll b, ll m) {
  ll n = (ll) sqrt(m) + 1, e = 1, f = 1, j = 1;
  unordered_map<ll, ll> A;
  while (j <= n && (e = f = e * a % m) != b % m)
    A[e * b % m] = j++;
  if (e == b % m) return j;
  if (__gcd(m, e) == __gcd(m, b))
    rep(i,2,n+2) if (A.count(e = e * f % m))
      return n * i - A[e];
  return -1;
}
