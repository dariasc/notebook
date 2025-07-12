/* -
name = "Side Of"
[info]
description = "Returns where $p$ is as seen from $s$ towards $e$. 1/0/-1 $<->$ left/on line/right. If the optional argument `eps` is given 0 is returned if $p$ is within distance `eps` from the line. It uses products in intermediate steps so watch out for overflow if using `int` or `ll`."
- */
template<class P>
ll sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }
template<class P>
ll sideOf(const P& s, const P& e, const P& p, double eps) {
  auto a = (e-s).cross(p-s);
  double l = (e-s).dist()*eps;
  return (a > l) - (a < -l);
}
