#include "../template.h"
/* -
name = "Dynamic Lazy Segment Tree"
[info]
time = "$O(log n)$"
- */
template <auto op, auto tag> struct SegmentTree {
  using T = decltype(op)::T;
  using U = decltype(tag)::U;
  struct Node {
    int l = -1, r = -1; 
    T x = op.e;
    U lz = tag.e;
  };
  int n;
  vec<Node> s;
  SegmentTree(int n) : n(n), s(1) {}
#define L s[v].l
#define R s[v].r
#define tm (tl+tr)/2
  T query(int l, int r, int v=0, int tl=0, int tr=0) { // [l,r)
    if (tr == 0) tr = n;
    if (v == -1 || r <= tl || tr <= l) return op.e;
    if (l <= tl && tr <= r) return s[v].x;
    push(v, tl, tr);
    return op(query(l, r, L, tl, tm), query(l, r, R, tm, tr));
  }
  int update(int l, int r, U u, int v=0, int tl=0, int tr=0) {
    if (tr == 0) tr = n;
    if (r <= tl || tr <= l) return v;
    if (v == -1) {
      s.emplace_back();
      v = sz(s) - 1;
    }
    if (l <= tl && tr <= r) {
      s[v].x = tag.apply(s[v].x, u, tl, tr);
      s[v].lz = tag(s[v].lz, u);
      return v;
    }
    push(v, tl, tr);
    L = update(l, r, u, L, tl, tm);
    R = update(l, r, u, R, tm, tr);
    s[v].x = op(s[L].x, s[R].x);
    return v;
  }
  void push(int v, int tl, int tr) {
    L = update(tl, tm, s[v].lz, L, tl, tm);
    R = update(tm, tr, s[v].lz, R, tm, tr);
    s[v].lz = tag.e;
  }
#undef L
#undef R
#undef tm
};
