#include "../template.h"
#include "value.h"
/* -
name = "Iterative Segment Tree"
[info]
description = "Iterative segment tree, with point update and range queries."
time = "$O(log n)$"
- */
template <class T> struct SegmentTree {
  vector<T> s;
  int n;
  SegmentTree(vec<T> &a) : s(2 * sz(a)), n(sz(a)) {
    for (int pos = 0; pos < n; pos++) {
      s[pos + n] = a[pos];
    }
    for (int pos = n - 1; pos >= 0; pos--) {
      s[pos] = T(s[pos * 2], s[pos * 2 + 1]);
    }
  }
  void update(int pos, T val) {
    for (s[pos += n].update(val); pos /= 2;) {
      s[pos] = T(s[pos * 2], s[pos * 2 + 1]);
    }
  }
  T query(int b, int e) { // [b, e)
    T ra, rb;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2)
        ra = T(ra, s[b++]);
      if (e % 2)
        rb = T(s[--e], rb);
    }
    return T(ra, rb);
  }
};
