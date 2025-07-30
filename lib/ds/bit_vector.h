#include "../template.h"
/* -
name = "Bit Vector"
[info]
- */
using ull = uint64_t;
struct BitVec {
  vec<pair<ull, int>> b;
  BitVec(const vec<bool>& a): b(sz(a) / 64 + 1) {
    rep(i,0,sz(a)) {
      auto& [x, y] = b[i >> 6];
      x |= ull(a[i]) << (i & 63), y += a[i];
    }
    rep(i,1,sz(b)) b[i].second += b[i - 1].second;
  }
  int rank(int r) {
    auto [x, y] = b[r >> 6];
    return y - popcount(x & -1ULL << (r & 63));
  }
};
