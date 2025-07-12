#include "../template.h"
/* -
name = "Fast Modular Multiplication"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/ModMulLL.h"
[info]
description = "Calculate $a dot b mod c$ (or $a^b mod c$) for $0 <= a, b <= c <= 7.2 dot 10^(18)$. `modmul` runs ~2x faster than the naive `(__int128_t)a * b % M`."
time = "$O(1)$ for `modmul`, $O(log e)$ for `modpow`."
- */
using ull = unsigned ll;
ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}
