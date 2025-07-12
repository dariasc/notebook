#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum" 
#include "../../lib/template.h"
#include "../../lib/ds/lazy_segment_tree.h"
#include "range_affine_op.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<ll> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  SegmentTree<Op{}, Tag{}> tree(n);
  tree.build(a);
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 0) {
      int b, c;
      cin >> b >> c;
      tree.update(l, r, array<ll, 2>{b, c});
    } else if (t == 1) {
      cout << tree.query(l, r) << "\n";
    }
  }
}
