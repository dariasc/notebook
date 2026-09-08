#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_7_C"
#define ERROR 0.00001
#include "../../lib/template.h"
#include "../../lib/geometry/circumcircle.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  P a, b, c;
  if (!(cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y)) return 0;
  P center = ccCenter(a, b, c);
  double r = ccRadius(a, b, c);
  cout << fixed << setprecision(8) << center.x << " " << center.y << " " << r << '\n';
}
