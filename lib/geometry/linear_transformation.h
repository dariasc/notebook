/* -
name = "Linear Transformation"
[info]
description = "Apply the linear transformation (translation, rotation and scaling) which takes line $a-b$ to line $c-d$ to point $r$."
- */
using P = Point<double>;
P linearTransformation(const P& a, const P& b,
    const P& c, const P& d, const P& r) {
  P dp = b-a, dq = d-c, num(dp.cross(dq), dp.dot(dq));
  return c + P((r-a).cross(num), (r-a).dot(num))/dp.dist2();
}
