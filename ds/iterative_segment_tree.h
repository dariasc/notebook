#include "../template.h"
/* -
name = "iterative_segment_tree"
[info]
description = "Iterative segment tree, with point update and range queries."
time = "$O(log n)$"
- */
struct value {
  ll x;
  value() : x(0) {}
  value(ll x) : x(x) {}
  value(value &a, value &b) { x = a.x + b.x; }
  void update(value &b) { x = b.x; }
};

template <class T> struct segment_tree {
  vector<T> s;
  int n;
  segment_tree(vec<T> &a) : s(2 * sz(a)), n(sz(a)) {
    for (int pos = 0; pos < n; pos++) {
      s[pos + n] = a[pos];
    }
    for (int pos = n - 1; pos >= 0; pos--) {
      s[pos] = T(s[pos * 2], s[pos * 2 + 1]);
    }
  }
  void update(int pos, T val) {
    for (s[pos += n].update(val); pos /= 2;) {
      s[pos] = T(s[pos * 2], s[pos * 2 + 1]);
    }
  }
  T query(int b, int e) { // query [b, e)
    assert(b < e);
    T ra, rb;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2)
        ra = T(ra, s[b++]);
      if (e % 2)
        rb = T(s[--e], rb);
    }
    return T(ra, rb);
  }
};
