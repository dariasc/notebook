#include "../template.h"
/* -
name = "Extended Euclidean Algorithm"
[info]
description = "Finds two integers $x$ and $y$, such that $a x+b y=gcd(a,b)$. If $a$ and $b$ are coprime, then $x$ is the inverse of $a$ modulo $b$."
time = "$O(log min(a,b))$"
- */
ll euclid(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a/b * x, d;
}
