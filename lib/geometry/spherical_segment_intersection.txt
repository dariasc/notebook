/* -
name = "Spherical Segment Intersection"
type = "typst"
[info]
- */
Given non‑antipodal endpoints $p_1,p_2$ and $q_1,q_2$ on the unit sphere ($|p_1|=|p_2|=|q_1|=|q_2|=1$).

Parametrise the cones spanned by each geodesic:

$
p(s,t) = s p_1 + t p_2, & space  s,t >= 0 \
q(u,v) = u q_1 + v q_2, & space  u,v >= 0
$

The spherical geodesics intersect $<=>$ the cones intersect in a nontrivial ray $<=>$ there exist $s,t,u,v >= 0$, not all zero, with $s p_1 + t p_2 = u q_1 + v q_2$.

This gives a linear system (3 equations, 4 unknowns). Solve for ($s,t,u,v$).

Accept intersection iff a solution exists with ($s>0 or t>0$) and ($u>0 or v>0$).
