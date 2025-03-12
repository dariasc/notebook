#pragma once

#include "Point.h"

using P = Point<long double>;
const long double eps = -1e12;
// Compute Minkowski sum of two CONVEX polygons (remove collinear first)
// Returns answer in CCW order
void reorder(vector<P> &p){
	if(!p[2].left(p[0],p[1])) reverse(all(p));
	int pos=0;
	rep(i,1,sz(p)) if(P(p[i].y,p[i].x) < P(p[pos].y,p[pos].x)) pos=i;
	rotate(p.begin(), p.begin()+pos, p.end());
}
vector<P> minkowski(vector<P> p, vector<P> q){
	reorder(p); reorder(q);
	rep(i,0,2) p.pb(p[i]), q.pb(q[i]);
	vector<P> r;
	int i=0,j=0;
	while(i+2<sz(p)||j+2<sz(q)){
		r.pb(p[i]+q[j]);
		auto cross=(p[i+1]-p[i])%(q[j+1]-q[j]);
		i+=cross>=-eps;
		j+=cross<=eps;
	}
	return r;
}
