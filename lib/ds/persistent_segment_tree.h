#include "../template.h"
/* -
name = "Persistent Segment Tree"
[info]
time = "$O(log n)$"
- */
template <class T> struct SegmentTree {
  struct Node {
    int l = 0, r = 0; 
    T x;
  };
  int n;
  vec<Node> s;
  vec<int> roots;
  SegmentTree(int n) : n(n), s(1), roots(1) {}
  T query(int i, int l, int r, int tl, int tr) {
    if (i == 0 || r <= tl || tr <= l) return T();
    if (l <= tl && tr <= r) return s[i].x;
    int tm = (tl+tr)/2;
    return T(query(s[i].l, l, r, tl, tm), 
             query(s[i].r, l, r, tm, tr));
  }
  T query(int ver, int l, int r) { // [l, r)
    return query(roots[ver], l, r, 0, n); 
  }
  int update(int i, int pos, T u, int tl, int tr) {
    s.push_back(s[i]);
    int j = sz(s) - 1;
    if (tr - tl == 1) {
      s[j].x.update(u);
    } else {
      int tm = (tl+tr)/2;
      if (pos < tm)
        s[j].l = update(s[j].l, pos, u, tl, tm);
      else
        s[j].r = update(s[j].r, pos, u, tm, tr);
      s[j].x = T(s[s[j].l].x, s[s[j].r].x);
    }
    return j;
  }
  int update(int ver, int pos, T u) {
    roots.push_back(update(roots[ver], pos, u, 0, n));
    return sz(roots) - 1;
  }
};
