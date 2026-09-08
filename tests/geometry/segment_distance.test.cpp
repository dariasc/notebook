#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_D"
#define ERROR 0.00000001
#include "../../lib/template.h"
#include "../../lib/geometry/segment_distance.h"
#include "../../lib/geometry/segment_intersection.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int q;
  if (!(cin >> q)) return 0;
  while (q--) {
    P p0, p1, p2, p3;
    cin >> p0.x >> p0.y >> p1.x >> p1.y;
    cin >> p2.x >> p2.y >> p3.x >> p3.y;
    if (!segInter(p0, p1, p2, p3).empty()) {
      cout << fixed << setprecision(10) << 0.0 << '\n';
    } else {
      double d1 = min(segDist(p0, p1, p2), segDist(p0, p1, p3));
      double d2 = min(segDist(p2, p3, p0), segDist(p2, p3, p1));
      cout << fixed << setprecision(10) << min(d1, d2) << '\n';
    }
  }
}
