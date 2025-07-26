#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching" 
#include "../../lib/template.h"
#include "../../lib/flow/hopcroft_karp.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int l, r, m;
  cin >> l >> r >> m;
  vec<vi> g(l);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
  }
  vi btoa(r, -1);
  hopcroftKarp(g, btoa);
  vec<array<int, 2>> ans;
  for (int j = 0; j < r; j++) {
    if (btoa[j] != -1) {
      ans.push_back({btoa[j], j});
    }
  }
  cout << sz(ans) << '\n';
  for (auto [i, j] : ans) {
    cout << i << " " << j << '\n';
  }
}

