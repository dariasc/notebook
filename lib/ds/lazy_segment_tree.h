#include "../template.h"
/* -
name = "Lazy Segment Tree"
[info]
time = "$O(log n)$"
- */
template <auto op, auto tag> struct SegmentTree {
  using T = decltype(op)::T;
  using U = decltype(tag)::U;
  int n;
  vec<T> s;
  vec<U> lz;
  SegmentTree(int n) : n(n), s(2*n-1, op.e), lz(2*n-1, tag.e) {}
#define L v+1
#define R v+2*(tm-tl)
#define tm (tl+tr)/2
  T query(int l, int r, int v=0, int tl=0, int tr=0) { // [l, r)
    if (tr == 0) tr = n;
    if (r <= tl || tr <= l) return op.e;
    if (l <= tl && tr <= r) return s[v];
    push(v, tl, tr);
    return op(query(l, r, L, tl, tm), query(l, r, R, tm, tr));
  }
  void update(int l, int r, U u, int v=0, int tl=0, int tr=0) { 
    if (tr == 0) tr = n;
    if (r <= tl || tr <= l) return;
    if (l <= tl && tr <= r) {
      s[v] = tag.apply(s[v], u, tl, tr);
      lz[v] = tag(lz[v], u);
      return;
    }
    push(v, tl, tr);
    update(l, r, u, L, tl, tm), update(l, r, u, R, tm, tr);
    s[v] = op(s[L], s[R]);
  }
  void push(int v, int tl, int tr) {
    update(tl, tm, lz[v], L, tl, tm);
    update(tm, tr, lz[v], R, tm, tr);
    lz[v] = tag.e;
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
