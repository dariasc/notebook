/* -
name = "Max Right"
[info]
description = "Finds max $m in (l, r]$ such that $f(m, text(\"prefix\"))$ is true ($l$ if none)."
time = "$O(log n)$"
- */
int max_right(int l, int r, auto f) {
  for (T x = e; l < r;) {
    int u = l + n, v = bit_width(min(u & -u, r - l) / 2u);
    int m = l + (1 << v);
    if (T y = op(x, s[u >> v]); f(m, y)) l = m, x = y;
    else r = m - 1;
  }
  return l;
}
