#include "../template.h"
/* -
name = "Segment Tree"
[info]
description = "Recursive segment tree, with point update and range queries."
time = "$O(log n)$"
- */
template <class T, auto op, class U=T> struct SegmentTree {
  int n;
  vec<T> s;
  SegmentTree(int n) : n(n), s(2*n-1) {}
#define L v+1
#define R v+2*(tm-tl)
#define tm (tl+tr)/2
  T query(int l, int r, int v=0, int tl=0, int tr=0) { // [l, r)
    if (tr == 0) tr = n;
    if (r <= tl || tr <= l) return op.e;
    if (l <= tl && tr <= r) return s[v];
    return op(query(l, r, L, tl, tm), query(l, r, R, tm, tr));
  }
  void update(int pos, U u, int v=0, int tl=0, int tr=0) {
    if (tr == 0) tr = n;
    if (tr - tl == 1) {
      s[v] = op.update(s[v], u);
    } else {
      if (pos < tm) update(pos, u, L, tl, tm);
      else update(pos, u, R, tm, tr);
      s[v] = op(s[L], s[R]);
    }
  }
  void build(vec<T> &a, int v=0, int tl=0, int tr=0) {
    if (tr == 0) tr = n;
    if (tr - tl == 1) {
      s[v] = a[tl];
    } else {
      build(a, L, tl, tm);
      build(a, R, tm, tr);
      s[v] = op(s[L], s[R]);
    }
  }
#undef L
#undef R
#undef tm
};
