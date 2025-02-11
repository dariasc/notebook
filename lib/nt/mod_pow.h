#include "../template.h"
/* -
name = "Modular Exponentiation"
[info]
time = "$O(log e)$"
- */
ll modpow(ll b, ll e) {
  ll r = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) r = r * b % mod;
  return r;
}
