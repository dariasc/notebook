#include "../template.h"
/* -
name = "iterative_segment_tree"
[info]
- */
template <class T, T unit, T F(T, T)> struct segment_tree {
  vector<T> s;
  int n;
  segment_tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = F(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2)
        ra = F(ra, s[b++]);
      if (e % 2)
        rb = F(s[--e], rb);
    }
    return F(ra, rb);
  }
};
