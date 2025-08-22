#include "point.h"
/* -
name = "Polygon Cut"
[info]
description = "Returns a vector with the vertices of a polygon with everything to the left of the line going from s to e cut away."
time = "$O(N)$"
- */
typedef Point<double> P;
vec<P> polygonCut(const vec<P>& poly, P s, P e) {
  vec<P> res;
  rep(i,0,sz(poly)) {
    P cur = poly[i], prev = i ? poly[i-1] : poly.back();
    auto a = s.cross(e, cur), b = s.cross(e, prev);
    if ((a < 0) != (b < 0))
      res.push_back(cur + (prev - cur) * (a / (a - b)));
    if (a < 0)
      res.push_back(cur);
  }
  return res;
}
