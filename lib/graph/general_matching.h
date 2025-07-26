#include "../template.h"
#include "../numerical/matrix_inv_mod.h"
/* -
name = "General Matching"
[info]
description = "Matching for general graphs. Fails with probability $N / mod$."
time = "$O(N^3)$"
- */
vec<pii> generalMatching(int N, vec<pii>& ed) {
  mt19937 mt(time(0));
  vec<vec<ll>> mat(N, vec<ll>(N)), A;
  for (auto [a, b] : ed) {
    int r = mt() % mod;
    mat[a][b] = r, mat[b][a] = (mod - r) % mod;
  }
  int r = matInv(A = mat), M = 2*N - r, fi, fj;
  assert(r % 2 == 0);
  if (M != N) do {
    mat.resize(M, vec<ll>(M));
    rep(i,0,N) {
      mat[i].resize(M);
      rep(j,N,M) {
        int r = mt() % mod;
        mat[i][j] = r, mat[j][i] = (mod - r) % mod;
      }
    }
  } while (matInv(A = mat) != M);
  vi has(M, 1); vec<pii> ret;
  rep(it,0,M/2) {
    rep(i,0,M) if (has[i])
      rep(j,i+1,M) if (A[i][j] && mat[i][j]) {
        fi = i; fj = j; goto done;
    } assert(0); done:
    if (fj < N) ret.emplace_back(fi, fj);
    has[fi] = has[fj] = 0;
    rep(sw,0,2) {
      ll a = modpow(A[fi][fj], mod-2);
      rep(i,0,M) if (has[i] && A[i][fj]) {
        ll b = A[i][fj] * a % mod;
        rep(j,0,M) A[i][j] = (A[i][j] - A[fi][j] * b) % mod;
      }
      swap(fi,fj);
    }
  }
  return ret;
}
