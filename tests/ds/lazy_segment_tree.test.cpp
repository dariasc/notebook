#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum" 
#include "../../lib/template.h"
#include "../../lib/ds/lazy_segment_tree.h"

const ll mod = 998244353;
struct Tag {
  ll b = 1, c = 0;
  ll map(ll x, int l, int r) const {
    return (x * b % mod + c * (r - l) % mod) % mod;
  }
  Tag operator()(Tag nu) const {
    return {
      b * nu.b % mod,
      (c * nu.b + nu.c) % mod
    };
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  auto mod_plus = [](ll a, ll b) { return (a+b) % mod; };
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
