#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum"
#include "../../lib/template.h"
#include "../../lib/graph/lct.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  LinkCut lct(n);
  rep(i,0,n) {
    ll a;
    cin >> a;
    lct.update(i + 1, a);
  }
  rep(i,0,n-1) {
    int u, v;
    cin >> u >> v;
    lct.link(u + 1, v + 1);
  }
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int u, v, w, x;
      cin >> u >> v >> w >> x;
      lct.cut(u + 1, v + 1);
      lct.link(w + 1, x + 1);
    } else if (type == 1) {
      int p;
      ll x;
      cin >> p >> x;
      lct.update(p + 1, lct.T[p + 1].self + x);
    } else {
      int u, v;
      cin >> u >> v;
      cout << lct.path(u + 1, v + 1) << '\n';
    }
  }
}
