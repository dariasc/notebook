#include "point.h"
#include "on_segment.h"
#include "segment_distance.h"
/* -
name = "Inside Polygon"
[info]
description = "Returns true if a point lies within the polygon. If strict is true, it returns false for points on the boundary."
time = "$O(n)$"
- */
template<class P>
bool inPolygon(vec<P> &p, P a, bool strict = true) {
  int cnt = 0, n = sz(p);
  rep(i,0,n) {
    P q = p[(i + 1) % n];
    if (onSegment(p[i], q, a)) return !strict;
    //or: if (segDist(p[i], q, a) <= eps) return !strict;
    cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
  }
  return cnt;
}
