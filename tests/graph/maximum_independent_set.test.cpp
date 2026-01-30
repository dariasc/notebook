#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"
#include "../../lib/template.h"
#include "../../lib/graph/maximum_clique.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m;
  cin >> n >> m;
  vb g(n);
  for (int i = 0; i < n; i++) {
    g[i].set();
    g[i][i] = 0;
  }
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    g[u][v] = 0;
    g[v][u] = 0;
  }
  vi S = MaxClique(g).maxClique();
  cout << sz(S) << '\n';
  for (int i : S) {
    cout << i << ' ';
  }
}
