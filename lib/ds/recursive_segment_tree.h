#include "../template.h"
/* -
name = "Segment Tree"
[info]
description = "Recursive segment tree, with point update and range queries."
time = "$O(log n)$"
- */
template <class T> struct SegmentTree {
  int n;
  vec<T> s;
  SegmentTree(int n) : n(n), s(2*n-1) {}
#define L v+1
#define R v+2*(tm-tl)
#define tm (tl+tr)/2
  T query(int l, int r, int v=0, int tl=0, int tr=0) { // [l, r)
    if (tr == 0) tr = n;
    if (r <= tl || tr <= l) return T();
    if (l <= tl && tr <= r) return s[v];
    return T(query(l, r, L, tl, tm), query(l, r, R, tm, tr));
  }
  void update(int pos, T x, int v=0, int tl=0, int tr=0) {
    if (tr == 0) tr = n;
    if (tr - tl == 1) {
      s[v].update(x);
    } else {
      if (pos < tm)
        update(pos, x, L, tl, tm);
      else
        update(pos, x, R, tm, tr);
      s[v] = T(s[L], s[R]);
    }
  }
  template <class V>
  void build(vec<V> &a, int v=0, int tl=0, int tr=0) {
    if (tr == 0) tr = n;
    if (tr - tl == 1) {
      s[v] = a[tl];
    } else {
      build(a, L, tl, tm);
      build(a, R, tm, tr);
      s[v] = T(s[L], s[R]);
    }
  }
#undef L
#undef R
#undef tm
};
