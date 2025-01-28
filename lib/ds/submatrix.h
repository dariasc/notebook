#include "../template.h"
/* -
name = "Sub Matrix"
[info]
description = "Calculate submatrix sums."
time = "$O(1)$"
- */
template <class T>
struct SubMatrix {
	vec<vec<T>> p;
	SubMatrix(vec<vec<T>>& v) {
		int R = sz(v), C = sz(v[0]);
		p.assign(R+1, vec<T>(C+1));
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				p[r+1][c+1] = v[r][c]+p[r][c+1]+p[r+1][c]-p[r][c];
			}
		}
	}
	T sum(int u, int l, int d, int r) { // [u, d) x [l, r)
		return p[d][r]-p[d][l]-p[u][r]+p[u][l];
	}
};
