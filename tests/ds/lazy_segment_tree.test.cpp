#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum" 
#include "../../lib/template.h"
#include "../../lib/ds/st/lazy_segment_tree.h"
#include "range_affine_op.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<ll> A(n);
  for (auto &a : A) {
    cin >> a;
  }
  SegmentTree<ll, mod_plus, 0, Tag, Tag{}> tree(n);
  tree.build(A);
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 0) {
      int b, c;
      cin >> b >> c;
      tree.upd(l, r, {b, c});
    } else if (t == 1) {
      cout << tree.query(l, r) << "\n";
    }
  }
}
