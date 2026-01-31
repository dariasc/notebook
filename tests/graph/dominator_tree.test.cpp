#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree"
#include "../../lib/template.h"
#include "../../lib/graph/dominator_tree.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m, s;
  cin >> n >> m >> s;
  vec<vi> g(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
  }
  auto tree = dominator_tree(g, s);
  vi p(n, -1);
  p[s] = s;
  for (int i = 0; i < n; i++)
    for (int j : tree[i]) p[j] = i;
  for (int i = 0; i < n; i++) cout << p[i] << ' ';
  cout << '\n';
}

