#include "../template.h"
/* -
name = "Push Relabel"
[info]
description = "Push-relabel using the highest label selection rule and the gap heuristic."
time = "$O\\(V^2 sqrt(E)\\)$" 
- */
struct PushRelabel {
  struct Edge {
    int to, rev;
    ll f, c;
    ll flow() { return max(f, ll(0)); }
  };
  vec<vec<Edge>> g;
  vec<ll> ec;
  vec<Edge*> cur;
  vec<vi> hs; vi H;
  PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}
  void addEdge(int s, int t, ll cap, ll rcap=0) {
    if (s == t) return;
    g[s].push_back({t, sz(g[t]), 0, cap});
    g[t].push_back({s, sz(g[s])-1, 0, rcap});
  }
  void addFlow(Edge& e, ll f) {
    Edge &back = g[e.to][e.rev];
    if (!ec[e.to] && f) hs[H[e.to]].push_back(e.to);
    e.f += f; e.c -= f; ec[e.to] += f;
    back.f -= f; back.c += f; ec[back.to] -= f;
  }
  ll calc(int s, int t) {
    int v = sz(g); H[s] = v; ec[t] = 1;
    vi co(2*v); co[0] = v-1;
    rep(i,0,v) cur[i] = g[i].data();
    for (Edge& e : g[s]) addFlow(e, e.c);
    for (int hi = 0;;) {
      while (hs[hi].empty()) if (!hi--) return -ec[s];
      int u = hs[hi].back(); hs[hi].pop_back();
      while (ec[u] > 0)  // discharge u
        if (cur[u] == g[u].data() + sz(g[u])) {
          H[u] = 1e9;
          for (Edge& e : g[u]) if (e.c && H[u] > H[e.to]+1)
            H[u] = H[e.to]+1, cur[u] = &e;
          if (++co[H[u]], !--co[hi] && hi < v)
            rep(i,0,v) if (hi < H[i] && H[i] < v)
              --co[H[i]], H[i] = v + 1;
          hi = H[u];
        } else if (cur[u]->c && H[u] == H[cur[u]->to]+1)
          addFlow(*cur[u], min(ec[u], cur[u]->c));
        else ++cur[u];
    }
  }
  bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};
