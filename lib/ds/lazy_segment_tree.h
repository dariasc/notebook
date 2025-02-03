#include "../template.h"
/* -
name = "Lazy Segment Tree"
[info]
time = "$O(log n)$"
- */
template <class T, class U> struct SegmentTree {
  int n;
  vec<T> s;
  vec<U> lz;
  SegmentTree(int n) : n(n), s(2 * n), lz(2 * n) {}
  int v(int tl, int tr) {
    return tr-tl > 1 ? (tl+tr)/2*2-1 : 2*tl;
  }
  T query(int l, int r, int tl, int tr) {
    if (r <= tl || tr <= l) 
      return T();
    if (l <= tl && tr <= r) 
      return s[v(tl,tr)];
    int tm = (tl+tr)/2;
    push(tl, tr);
    return T(query(l, r, tl, tm), query(l, r, tm, tr));
  }
  T query(int l, int r) { // [l, r)
    return query(l, r, 0, n);
  }
  void update(int l, int r, U x, int tl, int tr) { 
    if (r <= tl || tr <= l) 
      return;
    if (l <= tl && tr <= r)
      return s[v(tl,tr)] = x.apply(s[v(tl,tr)], tl, tr), 
             lz[v(tl,tr)].update(x);
    int tm = (tl+tr)/2;
    push(tl, tr);
    update(l, r, x, tl, tm);
    update(l, r, x, tm, tr);
    s[v(tl,tr)] = T(s[v(tl,tm)], s[v(tm,tr)]);
  }
  void update(int l, int r, U x) { // [l, r)
    update(l, r, x, 0, n);
  }
  void push(int tl, int tr) {
    int tm = (tl+tr)/2;
    U x = lz[v(tl,tr)];
    update(tl, tm, x, tl, tm);
    update(tm, tr, x, tm, tr);
    lz[v(tl,tr)] = U();
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
