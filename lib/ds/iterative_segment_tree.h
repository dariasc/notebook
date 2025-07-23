#include "../template.h"
/* -
name = "Iterative Segment Tree"
[info]
description = "Iterative segment tree, with point update and range queries. You can replace $s$ with a fast hashmap to get a dynamic segment tree."
time = "$O(log n)$"
- */
template <auto op> struct SegmentTree {
  using T = decltype(op)::T;
  using U = decltype(op)::U;
  vec<T> s;
  int n;
  SegmentTree(int n) : s(2 * n, op.e), n(n) {}
  void update(int i, U u) {
    for (i += n, s[i] = op.update(s[i], u); i /= 2;)
      s[i] = op(s[i * 2], s[i * 2 + 1]);
  }
  T query(int b, int e) { // [b, e)
    T ra = op.e, rb = op.e;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = op(ra, s[b++]);
      if (e % 2) rb = op(s[--e], rb);
    }
    return op(ra, rb);
  }
  void build(vec<T> &a) {
    rep(i,0,n)
      s[i + n] = a[i];
    for (int i = n - 1; i >= 0; i--)
      s[i] = op(s[i * 2], s[i * 2 + 1]);
  }
};
