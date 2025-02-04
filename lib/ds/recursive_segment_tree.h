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
  SegmentTree(int n) : n(n), s(2 * n) {}
  int v(int tl, int tr) {
    return tr-tl > 1 ? (tl+tr)/2*2-1 : 2*tl;
  }
  T query(int l, int r, int tl, int tr) {
    if (r <= tl || tr <= l) return T();
    if (l <= tl && tr <= r) return s[v(tl,tr)];
    int tm = (tl+tr)/2;
    return T(query(l, r, tl, tm),
             query(l, r, tm, tr));
  }
  T query(int l, int r) { // [l, r)
    return query(l, r, 0, n); 
  }
  void update(int pos, T x, int tl, int tr) {
    if (tr - tl == 1) {
      s[v(tl,tr)].update(x);
    } else {
      int tm = (tl+tr)/2;
      if (pos < tm)
        update(pos, x, tl, tm);
      else
        update(pos, x, tm, tr);
      s[v(tl,tr)] = T(s[v(tl,tm)], s[v(tm,tr)]);
    }
  }
  void update(int pos, T x) {
    return update(pos, x, 0, n);
  }
  template <class V>
  void build(vec<V> &a, int tl, int tr) {
    if (tr - tl == 1) {
      s[v(tl,tr)] = a[tl];
    } else {
      int tm = (tl+tr)/2;
      build(a, tl, tm);
      build(a, tm, tr);
      s[v(tl,tr)] = T(s[v(tl,tm)], s[v(tm,tr)]);
    }
  }
};
