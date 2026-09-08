#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_3_A"
#define ERROR 0.0001
#include "../../lib/template.h"
#include "../../lib/geometry/polygon_area.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n;
  cin >> n;
  vec<Point<double>> v(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i].x >> v[i].y;
  }
  double area = fabs(polygonArea2(v)) / 2.0;
  cout << fixed << setprecision(1) << area << '\n';
}
