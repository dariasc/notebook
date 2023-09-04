#include "../template.h"
/* -
name = "sparse_table"
[info]
time = "$O(n log n)$ preprocessing and $O(1)$ queries"
example = "`.query(inclusive, exclusive)`"
- */
template <class T> struct sparse_table {
  vec<vec<T>> jmp;
  T f(T a, T b) { return min(a, b); } // any idempotent function
  sparse_table(const vec<T> &V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
      jmp.emplace_back(sz(V) - pw * 2 + 1);
      for (int j = 0; j < sz(jmp[k]); j++)
        jmp[k][j] = f(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    assert(a < b); // or return inf if a == b
    int dep = 31 - __builtin_clz(b - a);
    return f(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};
