#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum" 
#include "../../lib/template.h"
#include "../../lib/graph/hld.h"
#include "../../lib/ds/st/lazy_segment_tree.h"

struct Tag {
  ll u = 0;
  ll map(ll x, int l, int r) const {
    return x + u*(r-l);
  }
  Tag operator()(Tag t) const {
    return {t.u + u};
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vi a(n);
  for (int &x : a) {
    cin >> x;
  }
  vec<vi> adj(n);
  for (int i = 0; i < n-1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  using st = SegmentTree<ll, plus{}, 0, Tag, Tag{}>;
  HLD<0, st> hld(adj);
  for (int u = 0; u < n; u++) {
    hld.modifyPath(u, u, Tag{a[u]});
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int u, x;
      cin >> u >> x;
      hld.modifyPath(u, u, Tag{x});
    } else {
      int u, v;
      cin >> u >> v;
      cout << hld.queryPath(u, v) << '\n';
    }
  }
}

