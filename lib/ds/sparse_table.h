#include "../template.h"
/* -
name = "Sparse Table"
[info]
time = "$O(n log n)$ preprocessing and $O(1)$ queries"
- */
template <class T> struct SparseTable {
  vec<vec<T>> jmp;
  SparseTable(const vec<T> &V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
      jmp.emplace_back(sz(V) - pw * 2 + 1);
      for (int j = 0; j < sz(jmp[k]); j++)
        jmp[k][j] = T(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int b, int e) { // [b, e)
    int dep = 31 - __builtin_clz(e - b);
    return T(jmp[dep][b], jmp[dep][e - (1 << dep)]);
  }
};
