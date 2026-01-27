#include "../../template.h"
/* -
name = "Persistent Lazy Segment Tree"
[info]
time = "$O(log n)$"
- */
template <class T, auto op, T e,
          class U, U id> struct SegmentTree {
  struct Node {
    int l = 0, r = 0; 
    T x = e;
    U lz = id;
  };
  int n;
  vec<Node> s;
  SegmentTree(int n) : n(n), s(1) {}
  int copy(int v) { 
    s.emplace_back(s[v]);
    return sz(s) - 1; 
  };
  T query(int l, int r, int v) { return query(l, r, v, 0, n); }
  T query(int l, int r, int v, int tl, int tr) { // [l,r)
    if (r <= tl || tr <= l) return e;
    if (l <= tl && tr <= r) return s[v].x;
    int t = sz(s);
    v = push(v, tl, tr);
    int tm = (tl+tr)/2;
    T val = op(query(l, r, s[v].l, tl, tm),
               query(l, r, s[v].r, tm, tr));
    s.resize(t);
    return val;
  }
  int upd(int l, int r, U u, int v) { return upd(l, r, u, v, 0, n); }
  int upd(int l, int r, U u, int v, int tl, int tr) {
    if (r <= tl || tr <= l) return v;
    if (l <= tl && tr <= r) {
      v = copy(v);
      s[v].x = u.map(s[v].x, tl, tr);
      s[v].lz = s[v].lz(u);
    } else {
      v = push(v, tl, tr);
      int tm = (tl+tr)/2;
      s[v].l = upd(l, r, u, s[v].l, tl, tm);
      s[v].r = upd(l, r, u, s[v].r, tm, tr);
      s[v].x = op(s[s[v].l].x, s[s[v].r].x);
    }
    return v;
  }
  int push(int v, int tl, int tr) {
    v = copy(v);
    if (tr - tl == 1) return v;
    int tm = (tl+tr)/2;
    s[v].l = upd(tl, tm, s[v].lz, s[v].l, tl, tm);
    s[v].r = upd(tm, tr, s[v].lz, s[v].r, tm, tr);
    s[v].lz = id;
    return v;
  }
};
