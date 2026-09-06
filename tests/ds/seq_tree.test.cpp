#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"
#include "../../lib/template.h"
#include "../../lib/ds/seq_tree.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<ll> a(n);
  for (auto& x : a) cin >> x;
  SeqTree tree(a);
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 0) tree.reverse(l, r);
    else cout << tree.query(l, r) << '\n';
  }
}
