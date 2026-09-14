/* -
name = "Min Left"
[info]
description = "Finds min $m in [l, r)$ such that $f(m, text(\"suffix\"))$ is true ($r$ if none)."
time = "$O(log n)$"
- */
int min_left(int l, int r, auto f) {
  for (T x = e; l < r;) {
    int u = r + n, v = bit_width(min(u & -u, r - l) / 2u);
    int m = r - (1 << v);
    if (T y = op(s[(u - 1) >> v], x); f(m, y)) r = m, x = y;
    else l = m + 1;
  }
  return r;
}
