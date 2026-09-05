#include "../template.h"
/* -
name = "Weighted Matroid Intersection"
source = "https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/matroid.cpp"
[info]
description = "Finds min weight independent set of maximal size."
time = "$O(r^3 n)$ with SPFA, $O(r^2 n log n)$ with Dijkstra with potentials"
- */
template <class T>
vi weightedMatroidInter(int n, vec<T> w, auto M1, auto M2) {
  using P = pair<T, int>;
  const P INF = {numeric_limits<T>::max(), INT_MAX};
  vec<bool> b(n), target(n), is_inside(n);
  vi I[2], from(n); vec<P> d(n);
  auto check_edge = [&](int u, int v) {
    return (b[u] && M1.oracle(u, v)) ||
           (b[v] && M2.oracle(v, u));
  };
  while (true) {
    I[0].clear(), I[1].clear();
    rep(u,0,n) I[b[u]].pb(u);
    M1.build(I[1]), M2.build(I[1]);
    rep(u,0,n)
      target[u] = is_inside[u] = 0, from[u] = -1, d[u] = INF;
    deque<T> q;
    sort(all(I[0]), [&](int i, int j) { return w[i] < w[j]; });
    for (int u : I[0]) {
      target[u] = M2.oracle(u);
      if (M1.oracle(u)) {
        if (is_inside[u]) continue;
        d[u] = {w[u], 0};
        (sz(q) && d[u] > d[q.front()]) ?
          q.pb(u) : q.push_front(u);
        is_inside[u] = true;
      }
    }
    while (sz(q)) {
      int u = q.front(); q.pop_front();
      is_inside[u] = false;
      for (int v : I[!b[u]]) if (check_edge(u, v)) {
        P nd = {d[u].first + w[v], d[u].second + 1};
        if (nd < d[v]) {
          from[v] = u, d[v] = nd;
          if (is_inside[v]) continue;
          (sz(q) && d[v] > d[q.front()]) ?
            q.pb(v) : q.push_front(v);
          is_inside[v] = true;
        }
      }
    }
    P mini = INF; int targ = -1;
    for (int u : I[0])
      if (target[u] && d[u] < mini) mini = d[targ = u];
    if (targ != -1) for (int u = targ; u != -1; u = from[u])
      b[u] = !b[u], w[u] *= -1;
    else break;
  }
  return I[1];
}
