#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_B"
#include "../../lib/template.h"
#include "../../lib/flow/mcmf.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m;
  ll f;
  cin >> n >> m >> f;
  MCMF mcmf(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    ll c, d;
    cin >> u >> v >> c >> d;
    mcmf.addEdge(u, v, c, d);
  }
  int s = 0, t = n - 1, sink = n;
  mcmf.addEdge(t, sink, f, 0);
  auto [totflow, totcost] = mcmf.maxflow(s, sink);
  if (totflow < f) {
    cout << -1 << '\n';
  } else {
    cout << totcost << '\n';
  }
}
