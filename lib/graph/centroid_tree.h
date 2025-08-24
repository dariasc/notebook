#include "../template.h"
/* -
name = "Centroid Tree"
[info]
description = "Calculate the centroid tree of a tree. Returns vector of fathers ($-1$ for root)."
time = "$O(N log N)$"
- */
vi centroidTree(vec<vi>& g) {
  int n = sz(g);
  vi vis(n), P(n), S(n);
  auto calc_sz = [&](auto&& self, int v, int p) -> int {
    S[v] = 1;
    for (int y : g[v]) if (y != p && !vis[y])
      S[v] += self(self, y, v);
    return S[v];
  };
  auto dfs = [&](auto&& self, int v, int p, int s) -> void {
    if (s < 0) s = calc_sz(calc_sz, v, -1);
    for (int y : g[v]) if (!vis[y] && S[y] * 2 >= s) {
      S[v] = 0;
      self(self, y, p, s);
      return;
    }
    vis[v] = 1;
    P[v] = p;
    for (int y : g[v]) if (!vis[y]) self(self, y, v, -1);
  };
  dfs(dfs, 0, -1, -1);
  return P;
}
