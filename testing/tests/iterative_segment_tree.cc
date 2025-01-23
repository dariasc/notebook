#include "../../lib/ds/iterative_segment_tree.h"
#include "../harness.h"

bool test(ull seed) {
  const ll mod = 5;
  mt19937_64 gen(seed);
  int n = 1000;
  vec<Value> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = {gen() % mod};
  }
  SegmentTree<Value> tree(a);
  int m = 10000;
  while (m--) {
    int t = gen() % 2;
    if (t == 0) {
      int i = gen() % n;
      a[i] = {gen() % mod};
      tree.update(i, {a[i]});
    } else {
      int i = gen() % n;
      int j = gen() % (n + 1);
      if (j < i) {
        swap(i, j);
      }
      if (i == j) {
        continue;
      }
      ll sum = 0;
      for (int k = i; k < j; k++) {
        sum += a[k].x;
      }
      if (sum != tree.query(i, j).x) {
        return 0;
      }
    }
  }
  return 1;
}
