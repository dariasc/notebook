#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum" 
#include "../../lib/template.h"
#include "../../lib/ds/lazy_segment_tree.h"
#include "range_affine_op.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  const ll mod = 998244353;
  auto mod_plus = [](ll a, ll b) { return (a+b) % mod; };
  auto mapping = [](ll x, auto u, int l, int r) {
    return (x * u[0] % mod + u[1] * (r - l) % mod) % mod;
  }
  auto compose = [](auto lz, auto u) { 
    return array<ll, 2>{
      lz[0] * u[0] % mod,
      (lz[1] * u[0] + u[1]) % mod
    }
  };
  SegmentTree<ll, mod_plus, 0
              array<ll, 2>, mapping, compose {1, 0}> tree(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 0) {
      int b, c;
      cin >> b >> c;
      tree.upd(l, r, array<ll, 2>{b, c});
    } else if (t == 1) {
      cout << tree.query(l, r) << "\n";
    }
  }
}
