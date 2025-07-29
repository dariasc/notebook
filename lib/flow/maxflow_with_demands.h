#include "../template.h"
/* -
name = "Flow with Demands"
[info]
description = "To find minimal flow that satisifes demands you can binary search over the capacity on the $t-s$ edge."
- */
template <class T> struct FlowDemands {
  int n;
  T mf;
  vec<ll> in, out;
  FlowDemands(int n): n(n), mf(n+2), in(n), out(n) {}
  void addEdge(int u, int v, ll cap, ll dem = 0) {
    mf.addEdge(u, v, cap - dem);
    out[u] += dem, in[v] += dem;
  }
  ll calc(int s, int t) {
    const ll inf = 1e9; // might need to be changed
    mf.addEdge(t, s, inf);
    rep(i,0,n) {
      mf.addEdge(n, i, in[i]);
      mf.addEdge(i, n+1, out[i]);
    }
    return mf.calc(n, n+1);
  }
};
