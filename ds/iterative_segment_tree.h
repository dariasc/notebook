#include "../template.h"
/* -
name = "iterative_segment_tree"
[info]
- */
template <class T, T F(T, T)> struct segment_tree {
  vec<T> s;
  int n;
  segment_tree(int n = 0) : s(2 * n), n(n) {}
  void build(vec<T> a) {
    for (int i = 0; i < n; i++)
      s[i + n] = a[i];
    for (int i = n - 1; i > 0; --i)
      s[i] = F(s[i * 2], s[i * 2 + 1]);
  }
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = F(s[pos * 2], s[pos * 2 + 1]);
  }
  T merge(T a, T b, bool ua, bool ub) {
    if (!ub)
      return a;
    if (!ua)
      return b;
    return F(a, b);
  }
  T query(int b, int e) { // query [b, e)
    bool ua = 0, ub = 0;
    T ra, rb;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) {
        ra = merge(ra, s[b++], ua, 1);
        ua = 1;
      }
      if (e % 2) {
        rb = merge(s[--e], rb, 1, ub);
        ub = 1;
      }
    }
    return merge(ra, rb, ua, ub);
  }
};
