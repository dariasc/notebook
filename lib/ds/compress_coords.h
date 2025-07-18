#include "../template.h"
/* -
name = "Coordinate Compression"
[info]
usage = "`vec<reference_wrapper<int>> X; X.pb(ref(x)); auto values = compress_coords(X);`"
- */
auto compress_coords(auto &X) {
  vi values;
  values.reserve(sz(X));
  sort(all(X));
  int i = -1, prev;
  for(auto &x : X) {
    if (i == -1 || x != prev) {
      i++;
      prev = x;
      values.pb(x);
    }
    x.get() = i;
  }
  return values;
}
