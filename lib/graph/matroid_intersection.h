#include "../template.h"
/* -
name = "Matroid Intersection"
source = "https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/matroid.cpp"
[info]
description = "Algorithms for finding maximum independent sets in the intersection of two matroids. `oracle(i)` is independent after adding $i$, `oracle(i, j)` ... after swapping $i$, $j$."
time = "$O(r^2 n)$ for unweighted. For weighted $O(r^3 n)$ with SPFA $O(r^2 n log n)$ with Dijkstra with potentials"
- */
vi matroidIntersection(int n, auto M1, auto M2) {
  vec<bool> b(n);
  vi I[2];
  bool converged = false;
  while (!converged) {
    I[0].clear(), I[1].clear();
    rep(u,0,n) I[b[u]].push_back(u);
    M1.build(I[1]), M2.build(I[1]);
    vec<bool> target(n), pushed(n);
    queue<int> q;
    for (int u : I[0]) {
      target[u] = M2.oracle(u);
      if (M1.oracle(u)) pushed[u] = true, q.push(u);
    }
    vi p(n, -1);
    converged = true;
    while (sz(q)) {
      int u = q.front(); q.pop();
      if (target[u]) {
        converged = false;
        for (int v = u; v != -1; v = p[v]) b[v] = !b[v];
        break;
      }
      for (int v : I[!b[u]]) if (!pushed[v]) {
        if ((b[u] && M1.oracle(u, v)) ||
            (b[v] && M2.oracle(v, u)))
          p[v] = u, pushed[v] = true, q.push(v);
      }
    }
  }
  return I[1];
}
template <class T>
vi weightedMatroidIntersection(
  int n, vec<T> w, auto M1, auto M2
) {
  vec<bool> b(n), target(n), is_inside(n);
  vi I[2], from(n);
  vec<pair<T, int>> d(n);
  auto check_edge = [&](int u, int v) {
    return (b[u] && M1.oracle(u, v)) ||
           (b[v] && M2.oracle(v, u));
  };
  while (true) {
    I[0].clear(), I[1].clear();
    rep(u,0,n) I[b[u]].push_back(u);
    M1.build(I[1]), M2.build(I[1]);
    rep(u,0,n) {
      target[u] = false, is_inside[u] = false, from[u] = -1;
      d[u] = {numeric_limits<T>::max(), INT_MAX};
    }
    deque<T> q;
    sort(all(I[0]), [&](int i, int j) { return w[i] < w[j]; });
    for (int u : I[0]) {
      target[u] = M2.oracle(u);
      if (M1.oracle(u)) {
        if (is_inside[u]) continue;
        d[u] = {w[u], 0};
        if (!q.empty() && d[u] > d[q.front()]) q.push_back(u);
        else q.push_front(u);
        is_inside[u] = true;
      }
    }
    while (sz(q)) {
      int u = q.front(); q.pop_front();
      is_inside[u] = false;
      for (int v : I[!b[u]]) if (check_edge(u, v)) {
        pair<T, int> nd(d[u].first + w[v], d[u].second + 1);
        if (nd < d[v]) {
          from[v] = u, d[v] = nd;
          if (is_inside[v]) continue;
          if (sz(q) && d[v] > d[q.front()]) q.push_back(v);
          else q.push_front(v);
          is_inside[v] = true;
        }
      }
    }
    pair<T, int> mini = pair(numeric_limits<T>::max(), INT_MAX);
    int targ = -1;
    for (int u : I[0]) if (target[u] && d[u] < mini) 
      mini = d[u], targ = u;
    if (targ != -1) for (int u = targ; u != -1; u = from[u])
      b[u] = !b[u], w[u] *= -1;
    else break;
  }
  return I[1];
}
