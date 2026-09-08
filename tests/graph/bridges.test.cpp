#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../../lib/template.h"
#include "../../lib/graph/bridges.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m;
  cin >> n >> m;
  vec<vec<pii>> g(n);
  rep(i,0,m) {
    int u, v;
    cin >> u >> v;
    g[u].pb({v, i});
    g[v].pb({u, i});
  }
  auto [num_ccs, br_id, is_br] = bridges(g, m);
  vec<vi> comps(num_ccs);
  rep(i,0,n) comps[br_id[i]].pb(i);
  cout << num_ccs << '\n';
  for (auto &c : comps) {
    cout << sz(c);
    for (int v : c) cout << ' ' << v;
    cout << '\n';
  }
}
