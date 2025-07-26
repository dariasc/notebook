#include "point.h"
/* -
name = "On Segment"
[info]
description = "Returns true iff $p$ lies on the line segment from $s$ to $e$."
- */
template<class P> bool onSegment(P s, P e, P p) {
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
