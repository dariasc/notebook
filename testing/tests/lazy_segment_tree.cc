#include "../../lib/ds/lazy_segment_tree.h"
#include "../harness.h"

bool test(ull seed) {
  const ll mod = 1e12;
  mt19937_64 gen(seed);
  int n = 1000;
  vec<Value> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = {gen() % mod};
  }
  Node<Value, Tag> tree(a, 0, n);
  int m = 10000;
  while (m--) {
    int t = gen() % 3;
    int l = gen() % n;
    int r = gen() % (n + 1);
    if (r < l) {
      swap(l, r);
    }
    if (l == r) {
      continue;
    }
    if (t == 0) {
      ll add_val = gen() % mod;
      tree.update(l, r, Tag{-1, add_val});
      for (int i = l; i < r; i++) {
        a[i].x += add_val;
      }
    } else if (t == 1) {
      ll set_val = gen() % mod;
      tree.update(l, r, Tag{set_val, 0});
      for (int i = l; i < r; i++) {
        a[i].x = set_val;
      }
    } else {
      ll tree_sum = tree.query(l, r).x;
      ll actual_sum = 0;
      for (int i = l; i < r; i++) {
        actual_sum += a[i].x;
      }
      if (tree_sum != actual_sum) {
        return false;
      }
    }
  }
  return true;
}
