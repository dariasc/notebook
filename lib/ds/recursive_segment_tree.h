#include "../template.h"
/* -
name = "Segment Tree"
[info]
description = "Recursive segment tree, with point update and range queries."
time = "$O(log n)$"
- */
template <class T, auto op, T e> struct SegmentTree {
  int n; vec<T> s;
  SegmentTree(int n) : n(n), s(2*n-1, e) {}
  T query(int l, int r, int v=0, int tl=0, int tr=0) { // [l, r)
    if (tr == 0) tr = n;
    if (r <= tl || tr <= l) return e;
    if (l <= tl && tr <= r) return s[v];
    int tm = (tl+tr)/2, L = v+1, R = v+2*(tm-tl);
    return op(query(l, r, L, tl, tm), query(l, r, R, tm, tr));
  }
  template <auto f, class U>
  void update(int pos, U u, int v=0, int tl=0, int tr=0) {
    if (tr == 0) tr = n;
    if (tr - tl == 1) {
      f(s[v], u);
    } else {
      int tm = (tl+tr)/2, L = v+1, R = v+2*(tm-tl);
      if (pos < tm) update<f>(pos, u, L, tl, tm);
      else update<f>(pos, u, R, tm, tr);
      s[v] = op(s[L], s[R]);
    }
  }
};
