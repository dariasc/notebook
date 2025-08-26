#include "../template.h"
/* -
name = "Matroid Intersection"
source = "https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/matroid.cpp"
[info]
description = "Algorithms for finding maximum independent sets in the intersection of two matroids. `oracle(i)` is independent after adding $i$, `oracle(i, j)` ... after swapping $i$, $j$."
time = "$O(r^2 n)$ for unweighted. For weighted $O(r^3 n)$ with SPFA $O(r^2 n log n)$ with Dijkstra with potentials"
- */
template<typename Matroid1, typename Matroid2>
vi matroidIntersection(int n, Matroid1 M1, Matroid2 M2) {
	vec<bool> b(n);
	vi I[2];
	bool converged = false;
	while (!converged) {
		I[0].clear(), I[1].clear();
		for (int u = 0; u < n; u++) I[b[u]].push_back(u);

		M1.build(I[1]), M2.build(I[1]);
		vec<bool> target(n), pushed(n);
		queue<int> q;
		for (int u : I[0]) {
			target[u] = M2.oracle(u);
			if (M1.oracle(u)) pushed[u] = true, q.push(u);
		}
		vi p(n, -1);
		converged = true;
		while (q.size()) {
			int u = q.front(); q.pop();
			if (target[u]) {
				converged = false;
				for (int v = u; v != -1; v = p[v]) b[v] = !b[v];
				break;
			}
			for (int v : I[!b[u]]) if (!pushed[v]) {
				if ((b[u] and M1.oracle(u, v)) or (b[v] and M2.oracle(v, u)))
					p[v] = u, pushed[v] = true, q.push(v);
			}
		}
	}
	return I[1];
}
template<typename T, typename Matroid1, typename Matroid2>
vi weightedMatroidIntersection(int n, vec<T> w, Matroid1 M1, Matroid2 M2) {
	vec<bool> b(n), target(n), is_inside(n);
	vi I[2], from(n);
	vec<pair<T, int>> d(n);
	auto check_edge = [&](int u, int v) {
		return (b[u] and M1.oracle(u, v)) or (b[v] and M2.oracle(v, u));
	};
	while (true) {
		I[0].clear(), I[1].clear();
		for (int u = 0; u < n; u++) I[b[u]].push_back(u);
		// I[1] contem o conjunto de tamanho I[1].size() de menor peso
		M1.build(I[1]), M2.build(I[1]);
		for (int u = 0; u < n; u++) {
			target[u] = false, is_inside[u] = false, from[u] = -1;
			d[u] = {numeric_limits<T>::max(), INF};
		}
		deque<T> q;
		sort(I[0].begin(), I[0].end(), [&](int i, int j){ return w[i] < w[j]; });
		for (int u : I[0]) {
			target[u] = M2.oracle(u);
			if (M1.oracle(u)) {
				if (is_inside[u]) continue;
				d[u] = {w[u], 0};
				if (!q.empty() and d[u] > d[q.front()]) q.push_back(u);
				else q.push_front(u);
				is_inside[u] = true;
			}
		}	
		while (q.size()) {
			int u = q.front(); q.pop_front();
			is_inside[u] = false;
			for (int v : I[!b[u]]) if (check_edge(u, v)) {
				pair<T, int> nd(d[u].first + w[v], d[u].second + 1);
				if (nd < d[v]) {
					from[v] = u, d[v] = nd;
					if (is_inside[v]) continue;
					if (q.size() and d[v] > d[q.front()]) q.push_back(v);
					else q.push_front(v);
					is_inside[v] = true;
				}
			}
		}
		pair<T, int> mini = pair(numeric_limits<T>::max(), INF);
		int targ = -1;
		for (int u : I[0]) if (target[u] and d[u] < mini) 
			mini = d[u], targ = u;	
		if (targ != -1) for (int u = targ; u != -1; u = from[u])
			b[u] = !b[u], w[u] *= -1;
		else break;
	}
	return I[1];
}
