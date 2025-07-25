#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"
#include "../../lib/template.h"
#include "../../lib/graph/bridges.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m;
  cin >> n >> m;
  vec<array<int, 3>> ed(m);
  vec<vec<array<int, 2>>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    ed[i] = {min(u, v), max(u, v), i};
    adj[u].push_back({v, i});
    adj[v].push_back({u, i});
  }
  sort(all(ed));
  auto [k, br_id, is_br] = bridges(adj, m);
  for (auto [u, v, i] : ed) {
    if (is_br[i]) {
      cout << u << ' ' << v << '\n';
    }
  }
}
