#define PROBLEM "https://judge.yosupo.jp/problem/static_convex_hull" 
#include "../../lib/template.h"
#include "../../lib/geometry/convex_hull.h"

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
    auto hull = convexHull(pts);
    cout << sz(hull) << '\n';
    for (int i = 0; i < sz(hull); i++) {
      cout << hull[i].x << " " << hull[i].y << '\n';
    }
  }
}
