/* -
name = "Minkowski"
[info]
description = "Compute Minkowski sum of two CONVEX polygons (remove collinear first). Returns answer in CCW order."
time = "$O(n + m)$"
- */
#include "Point.h"
using ld = long double;
using P = Point<ld>;
const long double eps = -1e12;
void reorder(vec<P> &p){
  if(!p[2].left(p[0],p[1])) reverse(all(p));
  int pos=0;
  rep(i,1,sz(p)) if(P(p[i].y,p[i].x) < P(p[pos].y,p[pos].x)) pos=i;
  rotate(p.begin(), p.begin()+pos, p.end());
}
vec<P> minkowski(vec<P> p, vec<P> q){
  reorder(p); reorder(q);
  rep(i,0,2) p.pb(p[i]), q.pb(q[i]);
  vec<P> r;
  int i = 0, j = 0;
  while (i+2<sz(p) || j+2<sz(q)){
    r.pb(p[i]+q[j]);
    auto cross = (p[i+1]-p[i])%(q[j+1]-q[j]);
    i += cross >= -eps;
    j += cross <= eps;
  }
  return r;
}
