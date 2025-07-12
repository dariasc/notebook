#define PROBLEM "https://judge.yosupo.jp/problem/closest_pair"
#include "../../lib/template.h"
#include "../../lib/geometry/closest_pair.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vec<P> pts(n);
    for (int i = 0; i < n; i++) {
      cin >> pts[i].x >> pts[i].y;
    }
    auto [a, b] = closest(pts);
    int l = -1, r = -1;
    for (int i = 0; i < n; i++) {
      if (l == -1 && pts[i] == a) {
        l = i;
      } else if (r == -1 && pts[i] == b) {
        r = i;
      }
    }
    cout << l << " " << r << '\n';
  }
}
