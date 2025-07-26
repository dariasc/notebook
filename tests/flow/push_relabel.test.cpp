#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching" 
#include "../../lib/template.h"
#include "../../lib/graph/push_relabel.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int l, r, m;
  cin >> l >> r >> m;
  PushRelabel mf(l + r + 2);
  int s = l + r;
  int t = s + 1;
  for (int i = 0; i < l; i++) {
    mf.addEdge(s, i, 1);
  }
  for (int i = 0; i < r; i++) {
    mf.addEdge(l + i, t, 1);
  }
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    mf.addEdge(a, l + b, 1);
  }
  mf.calc(s, t);
  vec<array<int, 2>> ans;
  for (int i = 0; i < l; i++) {
    for (auto e : mf.g[i]) {
      int j = e.to - l;
      if (e.flow() > 0 && j >= 0 && j < r) {
        ans.push_back({i, j});
      }
    }
  }
  cout << sz(ans) << '\n';
  for (auto [i, j] : ans) {
    cout << i << " " << j << '\n';
  }
}

