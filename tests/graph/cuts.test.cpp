#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include "../../lib/template.h"
#include "../../lib/graph/cuts.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m;
  cin >> n >> m;
  vec<array<int, 2>> ed(m);
  vec<vec<array<int, 2>>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    ed[i] = {u, v};
    adj[u].push_back({v, i});
    adj[v].push_back({u, i});
  }
  auto [k, bcc_id, is_cut] = cuts(adj, m);
  set<int> S;
  vec<set<int>> C(k);
  for (int i = 0; i < m; i++) {
    auto [u, v] = ed[i];
    C[bcc_id[i]].insert(u);
    C[bcc_id[i]].insert(v);
    S.insert(u);
    S.insert(v);
  }
  for (int i = 0; i < n; i++) {
    if (S.count(i) == 0) {
      C.pb(set<int>{i});
    }
  }
  cout << sz(C) << '\n';
  for (auto &v : C) {
    cout << sz(v) << ' ';
    for (auto x : v) {
      cout << x << ' ';
    }
    cout << '\n';
  }
}
