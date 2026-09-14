/* -
name = "Find First"
[info]
description = "First index in $[l, r)$ where $f(s[v], \"tl\", \"tr\")$ holds ($r$ if none). $f$ called at most once per subtree, in order."
time = "$O(log n)$"
- */
int find_first(int l, int r, auto f) {
  return find_first(l, r, f, 1, 0, n);
}
int down_first(auto f, int v, int tl, int tr) {
  if (v >= n) return tl;
  int tm = split(tl, tr);
  push(v, tl, tr);
  if (f(s[2*v], tl, tm)) return down_first(f, 2*v, tl, tm);
  return down_first(f, 2*v+1, tm, tr);
}
int find_first(int l, int r, auto f, int v, int tl, int tr) {
  if (r <= tl || tr <= l) return r;
  if (l <= tl && tr <= r)
    return f(s[v], tl, tr) ? down_first(f, v, tl, tr) : r;
  int tm = split(tl, tr);
  push(v, tl, tr);
  int res = find_first(l, r, f, 2*v, tl, tm);
  return res < r ? res : find_first(l, r, f, 2*v+1, tm, tr);
}
