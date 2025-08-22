#include "../template.h"
/* -
name = "Bellman Ford"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/BellmanFord.h"
[info]
description = "Calculates shortest paths from $s$ in a graph that might have negative edge weights. Unreachable nodes get $\"dist\" = inf$; nodes reachable through negative-weight cycles get $\"dist\" = -inf$. Assumes $V^2 max thin |w_i| < thin ~2^(63)$."
time = "$O(V E)$"
- */
const ll inf = LLONG_MAX;
struct Ed { int a, b, w, s() { return a < b ? a : -a; }};
struct Node { ll dist = inf; int prev = -1; };
void bellmanFord(vec<Node>& nodes, vec<Ed>& eds, int s) {
  nodes[s].dist = 0;
  sort(all(eds), [](Ed a, Ed b) { return a.s() < b.s(); });
  int lim = sz(nodes) / 2 + 2; // /3+100 with shuffled vertices
  rep(i,0,lim) for (Ed ed : eds) {
    Node cur = nodes[ed.a], &dest = nodes[ed.b];
    if (abs(cur.dist) == inf) continue;
    ll d = cur.dist + ed.w;
    if (d < dest.dist) {
      dest.prev = ed.a;
      dest.dist = (i < lim-1 ? d : -inf);
    }
  }
  rep(i,0,lim) for (Ed e : eds) {
    if (nodes[e.a].dist == -inf)
      nodes[e.b].dist = -inf;
  }
}
