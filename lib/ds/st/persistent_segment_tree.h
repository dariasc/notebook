#include "../../template.h"
/* -
name = "Persistent Segment Tree"
[info]
time = "$O(log n)$"
- */
template <class T, auto op, T e> struct SegmentTree {
  struct Node {
    int l = 0, r = 0; 
    T x = e;
  };
  int n;
  vec<Node> s;
  SegmentTree(int n) : n(n), s(1) {}
  int copy(int v) { 
    s.emplace_back(s[v]);
    return sz(s) - 1; 
  };
  T query(int l, int r, int v) { return query(l, r, v, 0, n); }
  T query(int l, int r, int v, int tl, int tr) { // [l, r)
    if (r <= tl || tr <= l) return e;
    if (l <= tl && tr <= r) return s[v].x;
    int tm = (tl+tr)/2;
    return op(query(l, r, s[v].l, tl, tm),
              query(l, r, s[v].r, tm, tr));
  }
  int upd(int pos, T u, int v) { return upd(pos, u, v, 0, n); } 
  int upd(int pos, T u, int v, int tl, int tr) {
    v = copy(v);
    if (tr - tl == 1) {
      s[v].x = u;
    } else {
      int tm = (tl+tr)/2;
      if (pos < tm) s[v].l = upd(pos, u, s[v].l, tl, tm);
      else s[v].r = upd(pos, u, s[v].r, tm, tr);
      s[v].x = op(s[s[v].l].x, s[s[v].r].x);
    }
    return v;
  }
};
