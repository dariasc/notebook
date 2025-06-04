#include "../template.h"
/* -
name = "Sparse Table"
[info]
time = "$O(n log n)$ preprocessing and $O(1)$ queries"
- */
template <class T, auto op> struct SparseTable {
  vec<vec<T>> jmp;
  SparseTable(vec<T> &a) : jmp(1, vec<T>(sz(a))) {
    for (int i = 0; i < sz(a); i++)
      jmp[0][i] = a[i];
    for (int pw = 1, k = 1; pw * 2 <= sz(a); pw *= 2, ++k) {
      jmp.emplace_back(sz(a) - pw * 2 + 1);
      for (int j = 0; j < sz(jmp[k]); j++)
        jmp[k][j] = op(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int b, int e) { // [b, e)
    int dep = 31 - __builtin_clz(e - b);
    return op(jmp[dep][b], jmp[dep][e - (1 << dep)]);
  }
};
