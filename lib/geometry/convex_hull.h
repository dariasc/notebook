#include "point.h"
/* -
name = "Convex Hull"
[info]
description = "Returns a vector of the points of the convex hull in *ccw* order. Points on the edge of the hull between two other points are not considered part of the hull."
time = "$O(n log n)$"
- */
using P = Point<ll>;
vec<P> convexHull(vec<P> pts) {
  if (sz(pts) <= 1) return pts;
  sort(all(pts));
  vec<P> h(sz(pts)+1);
  int s = 0, t = 0;
  for (int it = 2; it--; s = --t, reverse(all(pts)))
    for (P p : pts) {
      while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
      h[t++] = p;
    }
  return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
