#include "../../template.h"
#include "split.h"
/* -
name = "Lazy Segment Tree"
[info]
time = "$O(log n)$"
- */
template <class T, auto op, T e,
          class U, U id> struct SegmentTree {
  int n; vec<T> s; vec<U> lz;
  SegmentTree(int n) : n(n), s(2*n, e), lz(n, id) {}
  T query(int l, int r) { return query(l, r, 1, 0, n); }
  T query(int l, int r, int v, int tl, int tr) {
    if (r <= tl || tr <= l) return e;
    if (l <= tl && tr <= r) return s[v];
    push(v, tl, tr);
    int tm = split(tl, tr);
    return op(query(l, r, 2*v, tl, tm),
              query(l, r, 2*v+1, tm, tr));
  }
  void upd(int l, int r, U u) { return upd(l, r, u, 1, 0, n); }
  void upd(int l, int r, U u, int v, int tl, int tr) {
    if (r <= tl || tr <= l) return;
    if (l <= tl && tr <= r) { 
      s[v] = u.map(s[v], tl, tr);
      if (v < n) lz[v] = lz[v](u);
      return;
    }
    push(v, tl, tr);
    int tm = split(tl, tr);
    upd(l, r, u, 2*v, tl, tm), upd(l, r, u, 2*v+1, tm, tr);
    s[v] = op(s[2*v], s[2*v+1]);
  }
  void push(int v, int tl, int tr) {
    int tm = split(tl, tr);
    upd(tl, tm, lz[v], 2*v, tl, tm);
    upd(tm, tr, lz[v], 2*v+1, tm, tr);
    lz[v] = id;
  }
  void build(vec<T>& a) {
    auto pw2 = bit_ceil(size(a));
    for (int i = 0; i < n; i++)
      s[(i + pw2) % n + n] = a[i];
    for (int i = n - 1; i >= 1; i--)
      s[i] = op(s[2*i], s[2*i+1]);
  }
};
