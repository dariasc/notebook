#define PROBLEM "https://judge.yosupo.jp/problem/manhattanmst"
#include "../../lib/template.h"
#include "../../lib/ds/uf.h"
#include "../../lib/geometry/manhattan_mst.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n;
  cin >> n;
  vec<P> pts(n);
  for (auto &[x, y] : pts) {
    cin >> x >> y;
  }
  auto mst = manhattanMST(pts);
  sort(all(mst));
  UnionFind uf(n);
  vec<array<int, 2>> T;
  ll W = 0;
  for (auto [w, i, j] : mst) {
    if (uf.join(i, j)) {
      W += w;
      T.pb({i, j});
    }
  }
  cout << W << '\n';
  for (auto [i, j] : T) {
    cout << i << ' ' << j << '\n';
  }
}
