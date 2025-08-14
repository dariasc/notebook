/* -
name = "Polyhedron Volume"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/PolyhedronVolume.h"
[info]
description = "Magic formula for the volume of a polyhedron. Faces should point outwards."
- */
template <class V, class L>
double signedPolyVolume(const V& p, const L& trilist) {
  double v = 0;
  for (auto i : trilist) v += p[i.a].cross(p[i.b]).dot(p[i.c]);
  return v / 6;
}
