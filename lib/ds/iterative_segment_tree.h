#include "../template.h"
/* -
name = "Iterative Segment Tree"
[info]
description = "Iterative segment tree, with point update and range queries. You can replace $s$ with a fast hashmap to get a dynamic segment tree."
time = "$O(log n)$"
- */
template <class T, auto op, T e> struct SegmentTree {
  int n; vec<T> s;
  SegmentTree(int n) : n(n), s(2*n, e) {}
  T query(int a, int b) { // [a, b)
    T ra = e, rb = e;
    for (a += n, b += n; a < b; a /= 2, b /= 2) {
      if (a % 2) ra = op(ra, s[a++]);
      if (b % 2) rb = op(s[--b], rb);
    }
    return op(ra, rb);
  }
  void upd(int i, T u) {
    for (i += n, s[i] = u; i /= 2;)
      s[i] = op(s[i * 2], s[i * 2 + 1]);
  }
};
