#include "../template.h"
/* -
name = "Fast Subset Transform"
[info]
description = "Transform to a basis with fast convolutions of the form `c[z]` $= sum_(z = x plus.circle y)$ `a[x]` $dot$ `b[y]`, where $plus.circle$ is one of `AND`, `OR`, `XOR`. The size of $a$ must be a power of two."
time = "$O(n log n)$"
- */
void FST(auto& a, bool inv) {
  for (int n = sz(a), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) rep(j,i,i+step) {
      auto &u = a[j], &v = a[j + step]; tie(u, v) =
        inv ? pii(v - u, u) : pii(v, u + v); // AND
        // inv ? pii(v, u - v) : pii(u + v, u); // OR
        // pii(u + v, u - v);                   // XOR
    }
  }
  // if (inv) for (auto& x : a) x /= sz(a); // XOR only
}
auto conv(auto a, auto b) {
  FST(a, 0); FST(b, 0);
  rep(i,0,sz(a)) a[i] = a[i] * b[i];
  FST(a, 1); return a;
}
