#define PROBLEM "https://judge.yosupo.jp/problem/directedmst"
#include "../../lib/template.h"
#include "../../lib/graph/directed_mst.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m, s;
  cin >> n >> m >> s;
  vec<Edge> E(m);
  for (auto &[a, b, w] : E) {
    cin >> a >> b >> w;
  }
  auto [X, p] = dmst(n, s, E);
  cout << X << '\n';
  p[s] = s;
  for (int v : p) {
    cout << v << ' ';
  }
  cout << '\n';
}
