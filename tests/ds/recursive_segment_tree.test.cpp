#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum" 
#include "../../lib/template.h"
#include "../../lib/ds/value.h"
#include "../../lib/ds/recursive_segment_tree.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  SegmentTree<Value> tree(n);
  tree.build(a, 0, n);
  while (q--) {
    int t, a, b;
    cin >> t >> a >> b;
    if (t == 0) {
      tree.update(a, b);
    } else if (t == 1) {
      cout << tree.query(a, b) << "\n";
    }
  }
}

