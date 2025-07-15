#include "../template.h"
/* -
name = "Strongly Connected Components"
source = "https://github.com/IvanRenison/kactlpp/blob/gmat/content/graph/SCC.h"
[info]
description = "Finds strongly connected components in a directed graph. If vertices $u, v$ belong to the same component, we can reach $u$ from $v$ and vice versa. Returns the number of components and the component of each vertex. Natural order of components is reverse topological order (a component only has edges to components with lower index)."
time = "$O(V + E)$"
- */
pair<int, vi> scc(vec<vi>& g) {
  int n = sz(g), T = 0, num = 0;
  vi tin(n), comp(n, -1), z;
  function<int(int)> dfs = [&](int j) {
    int low = tin[j] = ++T, x; z.pb(j);
    for (int e : g[j]) if (comp[e] < 0)
      low = min(low, tin[e] ?: dfs(e));
    if (low == tin[j]) {
      do comp[x = z.back()] = num, z.pop_back();
      while (x != j);
      num++;
    }
    return tin[j] = low;
  };
  rep(i,0,n) if (comp[i] < 0) dfs(i);
  return {num, comp};
}
