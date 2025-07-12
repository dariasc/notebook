#define PROBLEM "https://judge.yosupo.jp/problem/primality_test" 
#include "../../lib/template.h"
#include "../../lib/nt/miller_rabin.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int q;
  cin >> q;
  while (q--) {
    ll a;
    cin >> a;
    if (isPrime(a)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }
}

