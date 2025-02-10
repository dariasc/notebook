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
  SegmentTree(int n) : n(n), s(2*n-1), lz(2*n-1) {}
#define L v+1
#define R v+2*(tm-tl)
#define tm (tl+tr)/2
  T query(int l, int r, int v=0, int tl=0, int tr=0) { // [l, r)
    if (tr == 0) tr = n;
    if (r <= tl || tr <= l) return T();
    if (l <= tl && tr <= r) return s[v];
    push(v, tl, tr);
    return T(query(l, r, L, tl, tm), query(l, r, R, tm, tr));
  }
  void update(int l, int r, U x, int v=0, int tl=0, int tr=0) { 
    if (tr == 0) tr = n;
    if (r <= tl || tr <= l) return;
    if (l <= tl && tr <= r)
      return s[v] = x.apply(s[v], tl, tr), lz[v].update(x);
    push(v, tl, tr);
    update(l, r, x, L, tl, tm);
    update(l, r, x, R, tm, tr);
    s[v] = T(s[L], s[R]);
  }
  void push(int v, int tl, int tr) {
    update(tl, tm, lz[v], L, tl, tm);
    update(tm, tr, lz[v], R, tm, tr);
    lz[v] = U();
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
