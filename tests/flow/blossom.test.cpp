#define PROBLEM "https://judge.yosupo.jp/problem/general_matching" 
#include "../../lib/template.h"
#include "../../lib/flow/blossom.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m;
  cin >> n >> m;
  vec<vi> g(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  auto mate = blossom(g);
  vec<pii> ans;
  for (int i = 0; i < n; i++) {
    if (mate[i] > i) {
      ans.pb({i, mate[i]});
    }
  }
  cout << sz(ans) << '\n';
  for (auto &[a, b] : ans) {
    cout << a << " " << b << '\n';
  }
}

