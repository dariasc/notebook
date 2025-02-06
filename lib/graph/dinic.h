#include "../template.h"
/* -
name = "Dinic"
[info]
time = "$O(V E log U)$ where $U = max thin |\"cap\"|$. $O\\(E min\\(E^(1/2), V^(2/3)\\)\\)$ if $U = 1$. $O\\(sqrt(V) E\\)$ for bipartite matching." 
- */
struct Dinic {
  struct Edge {
    int to, rev;
    ll c, oc;
    ll flow() { return max(oc - c, 0LL); }
  };
  vi lvl, ptr, q;
  vec<vec<Edge>> g;
  Dinic(int n) : lvl(n), ptr(n), q(n), g(n) {}
  void addEdge(int a, int b, ll c, ll rcap = 0) {
    g[a].push_back({b, sz(g[b]), c, c});
    g[b].push_back({a, sz(g[a]) - 1, rcap, rcap});
  }
  ll dfs(int v, int t, ll f) {
    if (v == t || !f) return f;
    for (int& i = ptr[v]; i < sz(g[v]); i++) {
      Edge& e = g[v][i];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, g[e.to][e.rev].c += p;
          return p;
        }
    }
    return 0;
  }
  ll calc(int s, int t) {
    ll flow = 0; q[0] = s;
    rep(L,0,31) do { // 'int L=30' maybe faster for random data
      lvl = ptr = vi(sz(q));
      int qi = 0, qe = lvl[s] = 1;
      while (qi < qe && !lvl[t]) {
        int v = q[qi++];
        for (Edge e : g[v])
          if (!lvl[e.to] && e.c >> (30 - L))
            q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
      }
      while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
    } while (lvl[t]);
    return flow;
  }
  bool leftOfMinCut(int a) { return lvl[a] != 0; }
};
