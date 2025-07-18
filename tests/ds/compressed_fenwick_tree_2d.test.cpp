#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"
#include "../../lib/template.h"
#include "../../lib/ds/compressed_fenwick_tree_2d.h"
#include "../../lib/ds/compress_coords.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<reference_wrapper<int>> X;
  vec<array<int, 3>> P(n);
  for (auto &[x, y, w] : P) {
    cin >> x >> y >> w;
    X.pb(ref(x));
  }
  vec<array<int, 4>> Q(q);
  for (auto &[l, d, r, u] : Q) {
    cin >> l >> d >> r >> u;
    X.pb(ref(l));
    X.pb(ref(r));
  }
  compress_coords(X);
  FT2 ft2(sz(X));
  for (auto &[x, y, w] : P) {
    ft2.fakeUpdate(x, y);
  }
  ft2.init();
  for (auto &[x, y, w] : P) {
    ft2.update(x, y, w);
  }
  for (auto &[l, d, r, u] : Q) {
    ll ans = 0;
    ans += ft2.query(r, u);
    ans -= ft2.query(r, d);
    ans -= ft2.query(l, u);
    ans += ft2.query(l, d);
    cout << ans << '\n';
  }
}
