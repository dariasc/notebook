#include "../template.h"
#include "miller_rabin.h"
/* -
name = "Factor"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/Factor.h"
[info]
description = "Pollard-rho randomized factorization algorithm. Returns prime factors of a number, in arbitrary order (e.g. $2299 -> {11, 19, 11}$)."
time = "$O\\(n^(1/4)\\)$"
- */
ull pollard(ull n) {
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	auto f = [&](ull x) { return modmul(x, x, n) + i; };
	while (t++ % 40 || __gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
vec<ull> factor(ull n) {
	if (n == 1) return {};
	if (isPrime(n)) return {n};
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), all(r));
	return l;
}
