#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"
#include "../../lib/template.h"
#include "../../lib/graph/2sat.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  string tmp;
  cin >> tmp >> tmp;
  int n, m;
  cin >> n >> m;
  TwoSat sat(n+1);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b >> tmp;
    if (a < 0) {
      a = ~(-a);
    }
    if (b < 0) {
      b = ~(-b);
    }
    sat.either(a, b);
  }
  if (sat.solve()) {
    cout << "s SATISFIABLE\n";
    cout << "v ";
    for (int i = 1; i <= n; i++) {
      cout << (sat.values[i] ? i : -i) << ' ';
    }
    cout << "0\n";
  } else {
    cout << "s UNSATISFIABLE\n";
  }
}

