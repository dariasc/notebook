#define PROBLEM "https://judge.yosupo.jp/problem/minimum_enclosing_circle"
#include "../../lib/template.h"
#include "../../lib/geometry/minimum_enclosing_circle.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n;
  cin >> n;
  vec<P> pts(n);
  for (int i = 0; i < n; i++) {
    cin >> pts[i].x >> pts[i].y;
  }
  auto [o, r] = mec(pts);
  for (int i = 0; i < n; i++) {
    if (fabs((o-pts[i]).dist2() - r*r) < 1e-6) {
      cout << "1";
    } else {
      cout << "0";
    }
  }
  cout << '\n';
}
