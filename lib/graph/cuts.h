#include "../template.h"
/* -
name = "Cuts"
source = "https://github.com/programming-team-code/programming_team_code/blob/dev/library/graphs/bridges_cuts/cuts.hpp"
[info]
description = "Finds cuts/articulation points in a graph. `g` is an adjacency list where each value is of type `{v, i}` $in$ `g[u]` where `i` is the index of the edge."
time = "$O(V + E)$"
- */
auto cuts(const auto& adj, int m) {
  int n = sz(adj), num_bccs = 0, q = 0, s = 0;
  vi bcc_id(m, -1), is_cut(n), tin(n), st(m);
  auto dfs = [&](auto&& self, int v, int p) -> int {
    int low = tin[v] = ++q;
    for (auto [u, e] : adj[v]) {
      assert(v != u);
      if (e == p) continue;
      if (tin[u] < tin[v]) st[s++] = e;
      int lu = -1;
      low = min(low, tin[u] ?: (lu = self(self, u, e)));
      if (lu >= tin[v]) {
        is_cut[v] = p >= 0 || tin[v] + 1 < tin[u];
        while (bcc_id[e] < 0) bcc_id[st[--s]] = num_bccs;
        num_bccs++;
      }
    }
    return low;
  };
  rep(i,0,n) 
    if (!tin[i]) dfs(dfs, i, -1);
  return tuple{num_bccs, bcc_id, is_cut};
}
