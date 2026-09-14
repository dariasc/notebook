/* -
name = "Find Last"
[info]
description = "Last index in $[l, r)$ where $f(s[v], \"tl\", \"tr\")$ holds ($l - 1$ if none). $f$ called at most once per subtree, in reverse order."
time = "$O(log n)$"
- */
int find_last(int l, int r, auto f) {
  return find_last(l, r, f, 1, 0, n);
}
int down_last(auto f, int v, int tl, int tr) {
  if (v >= n) return tl;
  int tm = split(tl, tr);
  push(v, tl, tr);
  if (f(s[2*v+1], tm, tr)) return down_last(f, 2*v+1, tm, tr);
  return down_last(f, 2*v, tl, tm);
}
int find_last(int l, int r, auto f, int v, int tl, int tr) {
  if (r <= tl || tr <= l) return l - 1;
  if (l <= tl && tr <= r)
    return f(s[v], tl, tr) ? down_last(f, v, tl, tr) : l - 1;
  int tm = split(tl, tr);
  push(v, tl, tr);
  int res = find_last(l, r, f, 2*v+1, tm, tr);
  return res >= l ? res : find_last(l, r, f, 2*v, tl, tm);
}
