#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"
#include "../../lib/template.h"
#include "../../lib/ds/op.h"
#include "../../lib/ds/persistent_segment_tree.h"
#include "../../lib/ds/compress_coords.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<reference_wrapper<int>> X, Y;
  vec<array<int, 3>> P(n);
  for (auto &[x, y, w] : P) {
    cin >> x >> y >> w;
    X.pb(ref(x));
    Y.pb(ref(y));
  }
  vec<array<int, 4>> Q(q);
  for (auto &[l, d, r, u] : Q) {
    cin >> l >> d >> r >> u;
    X.pb(ref(l));
    X.pb(ref(r));
    Y.pb(ref(d));
    Y.pb(ref(u));
  }
  auto values_X = compress_coords(X);
  auto values_Y = compress_coords(Y);
  vec<vec<array<int, 2>>> Yx(sz(values_Y));
  for (auto &[x, y, w] : P) {
    Yx[y].pb({x, w});
  }
  SegmentTree<Op{}> tree(sz(values_X));
  int ver = 0;
  vi last(sz(values_Y)+1);
  for (int y = 0; y < sz(Yx); y++) {
    for (auto [x, w] : Yx[y]) {
      ver = tree.update(x, w, ver);
    }
    last[y+1] = ver;
  }
  for (auto &[l, d, r, u] : Q) {
    cout << tree.query(l, r, last[u]) - tree.query(l, r, last[d]) << "\n"; 
  }
}
