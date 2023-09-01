/* -
name = "hashmap"
[info]
description = "Hash map with mostly the same API as unordered_map, but \\~3x faster. Uses 1.5x memory. Initial capacity must be a power of 2 (if provided)."
- */
#include <bits/extc++.h>
using namespace __gnu_pbds;

struct chash {
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};
gp_hash_table<ll,int,chash> h({},{},{},{},{1<<16});