#include "../template.h"
/* -
name = "Lazy Segment Tree"
[info]
time = "$O(log n)$"
- */
template <class T, auto op, T e,
          class U, auto m, auto c, U id> struct SegmentTree {
  int n; vec<T> s; vec<U> lz;
  SegmentTree(int n) : n(n), s(2*n-1, e), lz(2*n-1, id) {}
  T query(int l, int r) { return query(l, r, 0, 0, n); }
  T query(int l, int r, int v, int tl, int tr) {
    if (r <= tl || tr <= l) return e;
    if (l <= tl && tr <= r) return s[v];
    push(v, tl, tr);
    int tm = (tl+tr)/2, L = v+1, R = v+2*(tm-tl);
    return op(query(l, r, L, tl, tm), query(l, r, R, tm, tr));
  }
  void upd(int l, int r, U u) { return query(l, r, u, 0, 0, n); }
  void upd(int l, int r, U u, int v, int tl, int tr) {
    if (r <= tl || tr <= l) return;
    if (l <= tl && tr <= r) return apply(v, u);
    push(v, tl, tr);
    int tm = (tl+tr)/2, L = v+1, R = v+2*(tm-tl);
    update(l, r, u, L, tl, tm), update(l, r, u, R, tm, tr);
    s[v] = op(s[L], s[R]);
  }
  void apply(int v, U u) {
    s[v] = m(s[v], u);
    lz[v] = c(lz[v], u);
  }
  void push(int v, int tl, int tr) {
    if (tr - tl <= 1) return;
    int tm = (tl+tr)/2, L = v+1, R = v+2*(tm-tl);
    apply(L, lz[v]);
    apply(R, lz[v]);
    lz[v] = id;
  }
};
