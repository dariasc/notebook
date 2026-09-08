#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_C"
#define ERROR 0.00000001
#include "../../lib/template.h"
#include "../../lib/geometry/line_intersection.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int q;
  if (!(cin >> q)) return 0;
  while (q--) {
    Point<double> p0, p1, p2, p3;
    cin >> p0.x >> p0.y >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
    auto [res, pt] = lineInter(p0, p1, p2, p3);
    cout << fixed << setprecision(10) << pt.x << " " << pt.y << '\n';
  }
}
