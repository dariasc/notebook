#include "../template.h"
/* -
name = "Persistent Segment Tree"
[info]
time = "$O(log n)$"
- */
template <auto op> struct SegmentTree {
  using T = decltype(op)::T;
  using U = decltype(op)::U;
  struct Node {
    int l = 0, r = 0; 
    T x = op.e;
  };
  int n;
  vec<Node> s;
  SegmentTree(int n) : n(n), s(1) {}
#define L s[v].l
#define R s[v].r
#define tm (tl+tr)/2
  T query(int l, int r, int v, int tl=0, int tr=0) { // [l, r)
    if (tr == 0) tr = n;
    if (r <= tl || tr <= l) return op.e;
    if (l <= tl && tr <= r) return s[v].x;
    return op(query(l, r, L, tl, tm), query(l, r, R, tm, tr));
  }
  int update(int pos, U u, int v, int tl=0, int tr=0) {
    if (tr == 0) tr = n;
    s.emplace_back(s[v]);
    v = sz(s) - 1;
    if (tr - tl == 1) {
      s[v].x = op.update(s[v].x, u);
    } else {
      if (pos < tm) L = update(pos, u, L, tl, tm);
      else R = update(pos, u, R, tm, tr);
      s[v].x = op(s[L].x, s[R].x);
    }
    return v;
  }
#undef L
#undef R
#undef tm
};
