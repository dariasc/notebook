/* -
name = "kmp"
[info]
description = "`pi[x]` computes the length of the longest prefix of `s` that ends at `x`, other than `s[0...x]` itself (`abacaba` $->$ `0010123`). Can be used to find all occurrences of a string."
time = "$O(n)$"
- */
vector<int> pi(const string& s) {
	vi p(s.size());
	rep(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vector<int> match(const string& s, const string& pat) {
	vi p = pi(pat + '\0' + s), res;
	rep(i,sz(p)-sz(s),sz(p))
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}