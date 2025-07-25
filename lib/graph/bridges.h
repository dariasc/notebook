#include "../template.h"
/* -
name = "Bridges"
source = "https://github.com/programming-team-code/programming_team_code/blob/main/graphs/bridges_cuts/bridges.hpp"
[info]
description = "Finds bridges in a graph. `g` is an adjacency list where each value is of type `{v, i}` $in$ `g[u]` where `i` is the index of the edge."
time = "$O(V + E)$"
- */
auto bridges(const auto& g, int m) {
  int n = sz(g), num_ccs = 0, q = 0, s = 0;
  vi br_id(n, -1), is_br(m), tin(n), st(n);
  auto dfs = [&](auto&& self, int v, int p) -> int {
    int low = tin[v] = ++q;
    st[s++] = v;
    for (auto [u, e] : g[v])
      if (e != p && br_id[u] < 0)
        low = min(low, tin[u] ?: self(self, u, e));
    if (tin[v] == low) {
      if (p != -1) is_br[p] = 1;
      while (br_id[v] < 0) br_id[st[--s]] = num_ccs;
      num_ccs++;
    }
    return low;
  };
  rep(i,0,n)
    if (!tin[i]) dfs(dfs, i, -1);
  return tuple{num_ccs, br_id, is_br};
}
