
struct point {
	ll x,y;
	point(int xx = 0,int yy = 0) : x(xx),y(yy) {}
};
ll dist(const point& a,const point& b) {
	return ll((a.x-b.x))*(a.x-b.x) + ll((a.y-b.y))*(a.y-b.y);
}

point S[maxn];
point T[maxn];
bool cmpx(const point &lhs,const point &rhs) {
	return lhs.x < rhs.x;
}
bool cmpy(const point &lhs,const point &rhs) {
	return lhs.y < rhs.y;
}
inline ll sqr(ll a) {
	return a*a;
}

ll Closest_Pairs(int l,int r) {
	if(l == r)
		return inf;
	if(l == r-1)
		return dist(S[l],S[r]);
	int mid = (l + r) >> 1;
	ll ans = min(Closest_Pairs(l,mid),Closest_Pairs(mid+1,r));
	int k = 0;
	for(int i = l; i <= r; ++i) {
		if(sqr(S[i].x-S[mid].x) < ans) 
			T[k++] = S[i];
	}
	sort(T,T+k,cmpy);
	for(int i = 0; i < k; ++i) {
		for(int j = i + 1; j < k && sqr(T[j].y - T[i].y) < ans; ++j) {
			ans = min(ans,dist(T[j],T[i]));
		}
	}
	return ans;
}

