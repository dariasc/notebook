#include "../template.h"
/* -
name = "dinic"
[info]
time = "$O(V E log U)$"
- */
struct Dinic {
  struct EdgeFlow {
    int to, rev;
    ll c, oc;
    ll flow() { return max(oc - c, 0LL); } // if you need flows
  };
  vec<int> lvl, ptr, q;
  vec<vec<EdgeFlow>> adj;
  Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
  void addEdge(int a, int b, ll c, ll rcap = 0) {
    adj[a].push_back({b, sz(adj[b]), c, c});
    adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
  }
  ll dfs(int v, int t, ll f) {
    if (v == t || !f)
      return f;
    for (int &i = ptr[v]; i < sz(adj[v]); i++) {
      EdgeFlow &e = adj[v][i];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, adj[e.to][e.rev].c += p;
          return p;
        }
    }
    return 0;
  }
  ll calc(int s, int t) {
    ll flow = 0;
    q[0] = s;
    for (int L = 0; L < 31; L++) {
      do { // 'int L=30' maybe faster for random data
        lvl = ptr = vec<int>(sz(q));
        int qi = 0, qe = lvl[s] = 1;
        while (qi < qe && !lvl[t]) {
          int v = q[qi++];
          for (EdgeFlow e : adj[v])
            if (!lvl[e.to] && e.c >> (30 - L))
              q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
        }
        while (ll p = dfs(s, t, LLONG_MAX))
          flow += p;
      } while (lvl[t]);
    }
    return flow;
  }
  bool leftOfMinCut(int a) { return lvl[a] != 0; }
};
