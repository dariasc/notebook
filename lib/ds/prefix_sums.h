#include "../template.h"
/* -
name = "Prefix Sums"
[info]
description = "Calculate subarray sums."
time = "$O(1)$"
- */
template <class T> struct PrefixSum {
  vec<T> p;
  PrefixSum(vec<T>& v) {
    p.resize(sz(v)+1);
    for (int i = 0; i < sz(v); i++) {
      p[i+1] = p[i] + v[i];
    }
  }
  T sum(int b, int e) { // [b, e)
    return p[e] - p[b];
  }
};
