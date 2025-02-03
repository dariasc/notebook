#include "../template.h"
/* -
name = "Max Flow with Demands"
[info]
- */
template <class T> struct MaxFlowDemands {
  int n;
  T mf;
  vec<ll> in, out;
  MaxFlowDemands(int n): n(n), mf(n+2), in(n), out(n) {}
  void addEdge(int u, int v, ll cap, ll dem = 0) {
    mf.addEdge(u, v, cap - dem);
    out[u] += dem, in[v] += dem;
  }
  ll calc(int s, int t) {
    const ll inf = 1e9; // might need to be changed
    mf.addEdge(t, s, inf);
    for (int i = 0; i < n; i++) {
      mf.addEdge(n, i, in[i]);
      mf.addEdge(i, n+1, out[i]);
    }
    return mf.calc(n, n+1);
  }
};
