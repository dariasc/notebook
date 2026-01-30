#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod" 
#include "../../lib/template.h"
#include "../../lib/nt/mod_sqrt.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int q;
  cin >> q;
  while (q--) {
    ll y, p;
    cin >> y >> p;
    cout << sqrt(y, p) << '\n';
  }
}

