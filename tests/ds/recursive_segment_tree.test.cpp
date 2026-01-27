#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite" 
#include "../../lib/template.h"
#include "../../lib/ds/recursive_segment_tree.h"

const ll mod = 998244353;
array<ll, 2> compose(array<ll, 2> a, array<ll, 2> b) {
  return {b[0]*a[0] % mod, (b[0]*a[1] + b[1]) % mod};
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  SegmentTree<array<ll, 2>, compose, {1, 0}> tree(n);
  for (int i = 0; i < n; i++) {
    ll a, b;
    cin >> a >> b;
    tree.upd(i, {a, b});
  }
  while (q--) {
    int t, x, a, b;
    cin >> t >> x >> a >> b;
    if (t == 0) {
      tree.upd(x, {a, b});
    } else if (t == 1) {
      array<ll, 2> l = tree.query(x, a); 
      cout << (l[0]*b + l[1]) % mod << "\n";
    }
  }
}

