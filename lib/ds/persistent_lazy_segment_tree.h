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
  vec<int> roots;
  SegmentTree(int n) : n(n), s(1), roots(1) {}
  T query(int i, int l, int r, int tl, int tr) {
    if (i == 0 || r <= tl || tr <= l) return T();
    if (l <= tl && tr <= r) return s[i].x;
    int tm = (tl+tr)/2;
    push(i, tl, tr);
    return T(query(s[i].l, l, r, tl, tm), 
             query(s[i].r, l, r, tm, tr));
  }
  T query(int ver, int l, int r) { // [l, r)
    return query(roots[ver], l, r, 0, n); 
  }
  int update(int i, int l, int r, U u, int tl, int tr) {
    if (r <= tl || tr <= l) 
      return i;
    s.push_back(s[i]);
    int j = sz(s) - 1;
    if (l <= tl && tr <= r) {
      s[j].x = u.apply(s[j].x, tl, tr);
      s[j].lz.update(u);
    } else {
      int tm = (tl+tr)/2;
      push(j, tl, tr);
      s[j].l = update(s[j].l, l, r, u, tl, tm);
      s[j].r = update(s[j].r, l, r, u, tm, tr);
      s[j].x = T(s[s[j].l].x, s[s[j].r].x);
    }
    return j;
  }
  int update(int ver, int l, int r, U u) {
    roots.push_back(update(roots[ver], l, r, u, 0, n));
    return sz(roots) - 1;
  }
  void push(int i, int tl, int tr) {
    int tm = (tl+tr)/2;
    U u = s[i].lz;
    if (u != U()) {
      s[i].l = update(s[i].l, tl, tm, u, tl, tm);
      s[i].r = update(s[i].r, tm, tr, u, tm, tr);
      s[i].lz = U();
    }
  }
};
