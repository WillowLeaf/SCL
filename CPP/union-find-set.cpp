bool flag[maxm];
int h[maxn];
int p[maxm];
int r[maxm];
int k;

void init(int n) {
	k = n;
	memset(r,0,sizeof(r));
	for(int i = 0; i < n; ++i) {
		p[i] = i;
		h[i] = i;
	}
}

int find(int x) {
	if(p[x] == x) return x;
	return p[x] = find(p[x]);
}

void join(int x,int y) {
	const int fx = find(x), fy = find(y);
	if(r[fx] < r[fy]) {
		p[fx] = fy;
	} else {
		p[fy] = fx;
		if(r[fy] == r[fx]) r[fx]++;
	}
}

void remove(int x) {
	h[x] = k++;
	p[h[x]] = h[x];
}
