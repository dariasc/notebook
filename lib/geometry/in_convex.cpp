#pragma once
#include "point.h"
/* -
name = "Point in Convex Polygon"
[info]
description = "Given a strictly convex polygon p in CCW order, without repeating the first vertex, and a query point q, returns >0 if q is inside p, 0 if q is on its boundary, and <0 otherwise."
time = "$O(log n)$"
- */
template<class T>
T in_convex(const vector<Point<T>>& p, Point<T> q) {
  int n = p.size(); assert(n >= 3);
  int l = 1, r = n - 2;
  while (l != r) {
    int m = (l + r + 1) / 2;
    if (q.cross(p[0], p[m]) >= 0) l = m;
    else r = m - 1;
  }
  T in = min(q.cross(p[0], p[1]), q.cross(p[n-1], p[0]));
  return min(in, q.cross(p[l], p[l+1]));
}
