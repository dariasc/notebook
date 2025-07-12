#include "../template.h"
#include "modmul_ll.h"
/* -
name = "Miller Rabin"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/MillerRabin.h"
[info]
description = "Guaranteed to work for numbers up to $7 dot 10^(18)$; for larger numbers, use Python and extend A randomly."
time = "$|A| dot O(\"modpow\")$"
- */
bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}
