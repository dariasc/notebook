#include "../template.h"
/* -
name = "Longest Increasing Subsequence"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/various/LIS.h"
[info]
time = "$O(n log n)$"
- */
template<class I> 
vi lis(const vec<I>& S) {
	if (S.empty()) return {};
	vi prev(sz(S));
	using p = pair<I, int>;
	vec<p> res;
	rep(i,0,sz(S)) {
		// change 0 -> i for longest non-decreasing subsequence
		auto it = lower_bound(all(res), p{S[i], 0});
		if (it == res.end()) res.emplace_back(), it = res.end()-1;
		*it = {S[i], i};
		prev[i] = it == res.begin() ? 0 : (it-1)->second;
	}
	int L = sz(res), cur = res.back().second;
	vi ans(L);
	while (L--) ans[L] = cur, cur = prev[cur];
	return ans;
}
