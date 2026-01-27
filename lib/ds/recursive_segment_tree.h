#include "../template.h"
#include "split.h"
/* -
name = "Segment Tree"
[info]
description = "Recursive segment tree, with point update and range queries."
time = "$O(log n)$"
- */
template <class T, auto op, T e> struct SegmentTree {
  int n; vec<T> s;
  SegmentTree(int n) : n(n), s(2*n, e) {}
  T query(int l, int r) { return query(l, r, 1, 0, n); }
  T query(int l, int r, int v, int tl, int tr) {
    if (r <= tl || tr <= l) return e;
    if (l <= tl && tr <= r) return s[v];
    int tm = split(tl, tr);
    return op(query(l, r, 2*v, tl, tm), query(l, r, 2*v+1, tm, tr));
  }
  void upd(int pos, T u) { return upd(pos, u, 1, 0, n); };
  void upd(int pos, T u, int v, int tl, int tr) {
    if (tr - tl == 1) {
      s[v] = u;
    } else {
      int tm = split(tl, tr);
      if (pos < tm) upd(pos, u, 2*v, tl, tm);
      else upd(pos, u, 2*v+1, tm, tr);
      s[v] = op(s[2*v], s[2*v+1]);
    }
  }
};
