#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A"
#include "../../lib/template.h"
#include "../../lib/flow/push_relabel.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m;
  cin >> n >> m;
  PushRelabel pr(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    ll c;
    cin >> u >> v >> c;
    pr.addEdge(u, v, c);
  }
  cout << pr.calc(0, n - 1) << '\n';
}
