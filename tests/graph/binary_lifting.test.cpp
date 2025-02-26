#define PROBLEM "https://judge.yosupo.jp/problem/lca" 
#include "../../lib/template.h"
#include "../../lib/graph/binary_lifting.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<vi> adj(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    adj[i].push_back(p);
    adj[p].push_back(i);
  }
  Lift lca(adj);
  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << lca.lca(u, v) << '\n';
  }
}

