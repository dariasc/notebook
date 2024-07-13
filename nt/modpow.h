#include "../template.h"
/* -
name = "modpow"
[info]
time = "$O(log(e))$"
- */
const ll mod = 998244353; // faster if const
ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
