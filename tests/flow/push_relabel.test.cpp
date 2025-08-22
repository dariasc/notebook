#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A" 
#include "../../lib/template.h"
#include "../../lib/flow/push_relabel.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m;
  cin >> n >> m;
  PushRelabel mf(n);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    mf.addEdge(a, b, c);
  }
  cout << mf.calc(0, n-1) << '\n';
}

