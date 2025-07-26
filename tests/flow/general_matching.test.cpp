#define PROBLEM "https://judge.yosupo.jp/problem/general_matching" 
#include "../../lib/template.h"

const int mod = 998244353;

#include "../../lib/flow/general_matching.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m;
  cin >> n >> m;
  vec<pii> ed(m);
  for (auto &[a, b] : ed) {
    cin >> a >> b;
  }
  auto ans = generalMatching(n, ed);
  cout << sz(ans) << '\n';
  for (auto &[a, b] : ans) {
    cout << a << " " << b << '\n';
  }
}

