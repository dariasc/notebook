#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod" 
#include "../../lib/template.h"
#include "../../lib/nt/mod_log.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int q;
  cin >> q;
  while (q--) {
    ll x, y, m;
    cin >> x >> y >> m;
    if ((1 % m) == y) {
      cout << 0 << '\n';
    } else {
      cout << modLog(x, y, m) << '\n';
    }
  }
}

