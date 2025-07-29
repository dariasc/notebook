#include "../template.h"
#include "point.h"
#include "convex_hull.h"
#include "side_of.h"
/* -
name = "Minkowski"
[info]
description = "Compute Minkowski sum of two strictly convex non empty polygons (i.e. two hulls). Returns answer in *ccw* order."
time = "$O(n log n + m log m)$"
- */
void reorder(vec<P> &p) {
  if (sideOf(p[0], p[1], p[2]) < 0) reverse(all(p));
  rotate(p.begin(), min_element(all(p)), p.end());
}
vec<P> minkowskiSum(vec<P> p, vec<P> q) {
  if (min(sz(p), sz(q)) < 3) {
    vec<P> v;
    for (P pp : p) for (P qq : q) v.pb(pp + qq);
    return convexHull(v);
  }
  reorder(p), reorder(q);
  rep(i,0,2) p.pb(p[i]), q.pb(q[i]);
  vec<P> r;
  ll i = 0, j = 0;
  while (i + 2 < sz(p) || j + 2 < sz(q)) {
    r.pb(p[i] + q[j]);
    ll cross = (p[i + 1] - p[i]).cross(q[j + 1] - q[j]);
    i += cross >= 0, j += cross <= 0;
  }
  return r;
}
