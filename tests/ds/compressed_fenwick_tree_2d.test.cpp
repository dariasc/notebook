#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"
#include "../../lib/template.h"
#include "../../lib/ds/compressed_fenwick_tree_2d.h"

void make_unique(vec<int> &a) {
  sort(all(a));
  auto last = unique(all(a));
  a.erase(last, a.end());
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<int> X(n);
  vec<array<int, 3>> P(n);
  for (int i = 0; i < n; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    X[i] = x;
    P[i] = {x,y,w};
  }
  make_unique(X);
  FT2 ft2(sz(X));
  for (auto [x,y,w] : P) {
    int xi = lower_bound(all(X), x) - X.begin();
    ft2.fakeUpdate(xi, y);
  }
  ft2.init();
  for (auto [x,y,w] : P) {
    int xi = lower_bound(all(X), x) - X.begin();
    ft2.update(xi, y, w);
  }
  while (q--) {
    int l, d, r, u;
    cin >> l >> d >> r >> u;
    int li = lower_bound(all(X), l) - X.begin();
    int ri = lower_bound(all(X), r) - X.begin();
    ll ans = 0;
    ans += ft2.query(ri, u);
    ans -= ft2.query(ri, d);
    ans -= ft2.query(li, u);
    ans += ft2.query(li, d);
    cout << ans << '\n';
  }
}

