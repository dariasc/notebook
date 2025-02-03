#include "../template.h"
/* -
name = "Prefix Sums"
[info]
description = "Calculate subarray sums."
time = "$O(1)$"
- */
template <class T> struct PrefixSum {
  vec<T> p;
  SubMatrix(vec<T>& v) {
    int n = sz(v);
    p.assign(n+1, 0);
    for (int i = 0; i < n; i++) {
      p[i+1] = p[i] + v[i];
    }
  }
  T sum(int b, int e) { // [b, e)
    return p[b] - p[e];
  }
};
