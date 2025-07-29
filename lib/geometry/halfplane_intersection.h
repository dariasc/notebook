#include "../template.h"
#include "point.h"
#include "side_of.h"
#include "line_intersection.h"
/* -
name = "Halfplane Intersection"
[info]
description = "Computes the intersection of a set of half-planes. Input is given as a set of planes, facing left. The intersection must form a convex polygon or be empty. Output is the convex polygon representing the intersection in *ccw* order. The points may have duplicates and be collinear."
time = "$O(n log n)$"
- */
using P = Point<double>;
struct Line {
  P p, q;
  double a;
  Line() {}
  Line(P p, P q) : p(p), q(q), a((q - p).angle()) {}
  bool operator<(Line o) const { return a < o.a; }
};
vec<P> halfPlaneIntersection(vec<Line> v) {
  sort(all(v));
  ll n = sz(v), q = 1, h = 0;
  const double eps = 1e-9;
  vec<Line> c(n+2);
#define L(a) a.p, a.q
#define PQ(a) (a.q - a.p)
#define I(j, k) lineInter(L(c[j]), L(c[k])).snd
  rep(i,0,n) {
    while (q < h && sideOf(L(v[i]), I(h, h-1), eps) < 0) h--;
    while (q < h && sideOf(L(v[i]), I(q, q+1), eps) < 0) q++;
    c[++h] = v[i];
    if (q < h && abs(PQ(c[h]).cross(PQ(c[h-1]))) < eps) {
      if (PQ(c[h]).dot(PQ(c[h-1])) <= 0) return {};
      if (sideOf(L(v[i]), c[--h].p, eps) < 0) c[h] = v[i];
    }
  }
  while (q < h - 1 && sideOf(L(c[q]), I(h, h-1), eps) < 0) h--;
  while (q < h - 1 && sideOf(L(c[h]), I(q, q+1), eps) < 0) q++;
  if (h - q <= 1) return {};
  c[++h] = c[q];
  vec<P> s;
  rep(i,q,h) s.pb(I(i, i+1));
  return s;
#undef L
#undef PQ
#undef I
}
