/* -
name = "Split for Segment Tree"
[info]
- */
int split(int tl, int tr) {
  int pw2 = bit_floor(tr - tl + 0u);
  return min(tl + pw2, tr - pw2 / 2);
}
