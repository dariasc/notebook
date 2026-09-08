#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_3_C"
#include "../../lib/template.h"
#include "../../lib/geometry/inside_polygon.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n;
  if (!(cin >> n)) return 0;
  vec<Point<double>> poly(n);
  for (int i = 0; i < n; i++) {
    cin >> poly[i].x >> poly[i].y;
  }
  int q;
  cin >> q;
  while (q--) {
    Point<double> pt;
    cin >> pt.x >> pt.y;
    if (inPolygon(poly, pt, true)) {
      cout << 2 << '\n';
    } else if (inPolygon(poly, pt, false)) {
      cout << 1 << '\n';
    } else {
      cout << 0 << '\n';
    }
  }
}
