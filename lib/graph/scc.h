#include "../template.h"
/* -
name = "Strongly Connected Components"
source = "https://github.com/programming-team-code/programming_team_code/blob/main/graphs/strongly_connected_components/scc.hpp"
[info]
description = "Finds strongly connected components in a directed graph. If vertices $u, v$ belong to the same component, we can reach $u$ from $v$ and vice versa. Returns the number of components and the component of each vertex. Natural order of components is reverse topological order (a component only has edges to components with lower index)."
time = "$O(V + E)$"
- */
auto scc(const auto& g) {
  int n = sz(g), num_sccs = 0, q = 0, s = 0;
  vi scc_id(n, -1), tin(n), st(n);
  auto dfs = [&](auto&& self, int v) -> int {
    int low = tin[v] = ++q;
    st[s++] = v;
    for (int u : g[v])
      if (scc_id[u] < 0)
        low = min(low, tin[u] ?: self(self, u));
    if (tin[v] == low) {
      while (scc_id[v] < 0) scc_id[st[--s]] = num_sccs;
      num_sccs++;
    }
    return low;
  };
  rep(i,0,n)
    if (!tin[i]) dfs(dfs, i);
  return pair{num_sccs, scc_id};
}
