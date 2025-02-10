#include "../template.h"
/* -
name = "Persistent Lazy Segment Tree"
[info]
time = "$O(log n)$"
- */
template <class T, class U> struct SegmentTree {
  struct Node {
    int l = 0, r = 0; 
    T x;
    U lz;
  };
  int n;
  vec<Node> s;
  SegmentTree(int n) : n(n), s(1) {}
#define L s[v].l
#define R s[v].r
#define tm (tl+tr)/2
  T query(int l, int r, int v, int tl=0, int tr=0) { // [l,r)
    if (tr == 0) tr = n;
    if (r <= tl || tr <= l) return T();
    if (l <= tl && tr <= r) return s[v].x;
    push(v, tl, tr);
    return T(query(l, r, L, tl, tm), query(l, r, R, tm, tr));
  }
  int update(int l, int r, U u, int v, int tl=0, int tr=0) {
    if (tr == 0) tr = n;
    if (r <= tl || tr <= l) return v;
    s.push_back(s[v]);
    v = sz(s) - 1;
    if (l <= tl && tr <= r) {
      s[v].x = u.apply(s[v].x, tl, tr);
      s[v].lz.update(u);
    } else {
      push(v, tl, tr);
      L = update(l, r, u, L, tl, tm);
      R = update(l, r, u, R, tm, tr);
      s[v].x = T(s[L].x, s[R].x);
    }
    return v;
  }
  void push(int v, int tl, int tr) {
    if (s[v].lz != U()) {
      L = update(tl, tm, s[v].lz, L, tl, tm);
      R = update(tm, tr, s[v].lz, R, tm, tr);
      s[v].lz = U();
    }
  }
#undef L
#undef R
#undef tm
};
