#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_B"
#include "../../lib/template.h"
#include "../../lib/geometry/segment_intersection.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int q;
  if (!(cin >> q)) return 0;
  while (q--) {
    Point<double> p0, p1, p2, p3;
    cin >> p0.x >> p0.y >> p1.x >> p1.y;
    cin >> p2.x >> p2.y >> p3.x >> p3.y;
    auto inter = segInter(p0, p1, p2, p3);
    cout << (!inter.empty() ? 1 : 0) << '\n';
  }
}
