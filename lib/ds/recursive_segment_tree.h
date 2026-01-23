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
  T query(int l, int r) { return query(l, r, 0, 0, n); }
  T query(int l, int r, int v, int tl, int tr) {
    if (r <= tl || tr <= l) return e;
    if (l <= tl && tr <= r) return s[v];
    int tm = (tl+tr)/2, L = v+1, R = v+2*(tm-tl);
    return op(query(l, r, L, tl, tm), query(l, r, R, tm, tr));
  }
  void upd(int pos, T u) { return upd(pos, u, 0, 0, n); };
  void upd(int pos, T u, int v, int tl, int tr) {
    if (tr - tl == 1) {
      s[v] = u;
    } else {
      int tm = (tl+tr)/2, L = v+1, R = v+2*(tm-tl);
      if (pos < tm) update(pos, u, L, tl, tm);
      else update(pos, u, R, tm, tr);
      s[v] = op(s[L], s[R]);
    }
  }
};
