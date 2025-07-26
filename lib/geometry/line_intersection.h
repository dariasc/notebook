/* -
name = "Line Intersection"
[info]
description = "If a unique intersection point of the lines going through `a,b` and `c,d` exists ${1, \"point\"}$ is returned. If no intersection point exists ${0, (0,0)}$ is returned and if infinitely many exists ${-1, (0,0)}$ is returned. The wrong position will be returned if `P` is `Point<ll>` and the intersection point does not have integer coordinates. Products of three coordinates are used in intermediate steps so watch out for overflow if using `int` or `ll`."
- */
template<class P>
pair<int, P> lineInter(P a, P b, P c, P d) {
  auto d = (b - a).cross(d - c);
  if (d == 0) // if parallel
    return {-(a.cross(b, c) == 0), P(0, 0)};
  auto p = c.cross(b, d), q = c.cross(d, a);
  return {1, (a * p + b * q) / d};
}
