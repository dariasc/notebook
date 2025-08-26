#include "../template.h"
/* -
name = "Morbius"
[info]
time = "$O(L log L)$"
- */
const int L = 1e6;
array<int8_t, L> mu;
void calculateMu() {
  mu[1] = 1;
  rep(i,1,L) if (mu[i]) for (int j=2*i; j<L; j+=i) mu[j] -= mu[i];
}
