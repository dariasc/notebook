#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum" 
#include "../../lib/template.h"
#include "../../lib/ds/op.h"
#include "../../lib/ds/recursive_segment_tree.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  SegmentTree<ll, plus<ll>{}, 0> tree(n);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    auto assign = [] (ll &y, ll u) { y = u; };
    tree.update<assign>(i, x);
  }
  while (q--) {
    int t, a, b;
    cin >> t >> a >> b;
    if (t == 0) {
      auto add = [] (ll &y, ll u) { y += u; };
      tree.update<add>(a, b);
    } else if (t == 1) {
      cout << tree.query(a, b) << "\n";
    }
  }
}

