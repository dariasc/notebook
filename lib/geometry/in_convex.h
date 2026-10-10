#pragma once
#include "point.h"
/* -
name = "Point in Convex Polygon"
[info]
description = "Given a strictly convex polygon $p$ in *ccw* order, without repeating the first vertex, and a query point $q$, returns $>0$ if $q$ is inside $p$, $0$ if $q$ is on its boundary, and $<0$ otherwise."
time = "$O(log n)$"
- */
template <class P>
auto inConvex(const vec<P>& p, P q) {
  int l = *ranges::partition_point(views::iota(2, sz(p) - 1),
    [&](int m) { return q.cross(p[0], p[m]) >= 0; }) - 1;
  auto in = min(q.cross(p[0], p[1]), q.cross(p[sz(p)-1], p[0]));
  return min(in, q.cross(p[l], p[l+1]));
}
