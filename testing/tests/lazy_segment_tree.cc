#include "../../lib/ds/lazy_segment_tree.h"
#include "../harness.h"

bool test(ull seed) {
  const ll mod = 1e12;
  mt19937_64 gen(seed);
  int n = 1000;
  vec<ll> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = random(gen, mod);
  }
  Node<Value, Tag> tree(a, 0, n);
  int m = 10000;
  while (m--) {
    int t = random(gen, 3);
    int l = random(gen, n);
    int r = random(gen, n + 1);
    if (r < l) {
      swap(l, r);
    }
    if (l == r) {
      continue;
    }
    if (t == 0) {
      ll add_val = random(gen, mod);
      tree.update(l, r, Tag{-1, add_val});
      for (int i = l; i < r; i++) {
        a[i] += add_val;
      }
    } else if (t == 1) {
      ll set_val = random(gen, mod);
      tree.update(l, r, Tag{set_val, 0});
      for (int i = l; i < r; i++) {
        a[i] = set_val;
      }
    } else {
      ll tree_sum = tree.query(l, r);
      ll actual_sum = 0;
      for (int i = l; i < r; i++) {
        actual_sum += a[i];
      }
      if (tree_sum != actual_sum) {
        return false;
      }
    }
  }
  return true;
}
