#define PROBLEM "https://judge.yosupo.jp/problem/scc" 
#include "../../lib/template.h"
#include "../../lib/graph/scc.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m;
  cin >> n >> m;
  vec<vi> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }
  auto [k, C] = scc(adj);
  vec<vi> ans(k);
  for (int i = 0; i < n; i++) {
    ans[C[i]].push_back(i);
  }
  reverse(all(ans));
  cout << k << '\n';
  for (auto &v : ans) {
    cout << sz(v) << " ";
    for (int x : v) {
      cout << x << " ";
    }
    cout << '\n';
  }
}
