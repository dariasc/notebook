#define PROBLEM "https://judge.yosupo.jp/problem/lca" 
#include "../../lib/template.h"
#include "../../lib/ds/mo.h"

vi D;
void dfs(int v, int p, int d, vec<vi>& adj) {
  D[v] = d;
  for (int u : adj[v]) if (u != p) {
    dfs(u, v, d+1, adj);
  }
}

pii lca = {1e9, -1};
deque<pii> path;
void add(int v, int end) {
  pii N = {D[v], v};
  lca = min(lca, N);
  if (end == 0) {
    path.push_front(N);
  } else {
    path.push_back(N);
  }
}
void del(int v, int end) {
  pii N = {D[v], v};
  if (lca == N || sz(path) == 0) {
    lca = {1e9, -1};
  }
	if (end == 0) {
		path.pop_front();
	} else {
		path.pop_back();
	}
  if (sz(path) > 0) {
    lca = min(lca, path.back());
    lca = min(lca, path.front());
  }
}
int calc() {
  return lca.second;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<vi> adj(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    adj[i].push_back(p);
    adj[p].push_back(i);
  }
  D = vi(n);
  dfs(0, -1, 0, adj);
  vec<array<int, 2>> Q(q);
  for (int i = 0; i < q; i++) {
    cin >> Q[i][0] >> Q[i][1]; 
  }
  vi r = moTree(Q, adj);
  for (int x : r) {
    cout << x << '\n';
  }
}

