#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min" 
#include "../../lib/template.h"
#include "../../lib/ds/convex_hull_trick.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  LineContainer cht;
  while (n--) {
    ll a, b;
    cin >> a >> b;
    cht.add(-a, -b);
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      ll a, b;
      cin >> a >> b;
      cht.add(-a, -b);
    } else if (t == 1) {
      ll x;
      cin >> x;
      cout << -cht.query(x) << '\n';
    }
  }
}

