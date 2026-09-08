#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_4_C"
#define ERROR 0.00001
#include "../../lib/template.h"
#include "../../lib/geometry/polygon_cut.h"
#include "../../lib/geometry/polygon_area.h"

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
    Point<double> p1, p2;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    auto cut = polygonCut(poly, p2, p1);
    double area = (sz(cut) >= 3 ? fabs(polygonArea2(cut)) / 2.0 : 0.0);
    cout << fixed << setprecision(8) << area << '\n';
  }
}
