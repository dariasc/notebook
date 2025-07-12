#define PROBLEM "https://judge.yosupo.jp/problem/factorize" 
#include "../../lib/template.h"
#include "../../lib/nt/factor.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int q;
  cin >> q;
  while (q--) {
    ll a;
    cin >> a;
    vec<ull> f = factor(a);
    sort(all(f));
    cout << sz(f) << " ";
    for (ull x : f) {
      cout << x << " ";
    }
    cout << '\n';
  }
}

