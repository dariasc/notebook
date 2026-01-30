#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"
#include "../../lib/template.h"
#include "../../lib/nt/mod_sum.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int q;
  cin >> q;
  while (q--) {
    ll n, m, a, b;
    cin >> n >> m >> a >> b;
    cout << divsum(n, b, a, m) << '\n';
  }
}
