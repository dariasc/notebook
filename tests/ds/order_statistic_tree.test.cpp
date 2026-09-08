#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"
#include "../../lib/template.h"
#include "../../lib/ds/order_statistic_tree.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  Tree<int> S;
  rep(i,0,n) {
    int x;
    cin >> x;
    S.insert(x);
  }
  while (q--) {
    int t, x;
    cin >> t >> x;
    if (t == 0) {
      S.insert(x);
    } else if (t == 1) {
      S.erase(x);
    } else if (t == 2) {
      if (x > sz(S)) cout << -1 << '\n';
      else cout << *S.find_by_order(x - 1) << '\n';
    } else if (t == 3) {
      cout << S.order_of_key(x + 1) << '\n';
    } else if (t == 4) {
      auto it = S.upper_bound(x);
      if (it == S.begin()) cout << -1 << '\n';
      else cout << *prev(it) << '\n';
    } else if (t == 5) {
      auto it = S.lower_bound(x);
      if (it == S.end()) cout << -1 << '\n';
      else cout << *it << '\n';
    }
  }
}
