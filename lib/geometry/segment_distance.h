#include "point.h"
/* -
name = "Segment Distance"
[info]
description = "Returns the shortest distance between point $p$ and the line segment from point $s$ to $e$."
- */
using P = Point<double>;
double segDist(P& s, P& e, P& p) {
  if (s==e) return (p-s).dist();
  auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
  return ((p-s)*d-(e-s)*t).dist()/d;
}
