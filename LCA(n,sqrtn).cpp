const int maxn = 40050;
const int inf = 0x3f3f3f3f;

struct edge{
	int v,w;
	edge(int vv,int ww):v(vv),w(ww) {}
};
vector<edge> g[maxn];
int l[maxn],p[maxn],t[maxn],dist[maxn];
int N,M,width,rt;
void dfs(int u,int pre) {
	for(int i = 0; i < g[u].size(); ++i) {
		const int v = g[u][i].v, w = g[u][i].w;
		if(v != pre) {
			l[v] = l[u] + 1;
			dist[v] = dist[u] + w;
			t[v] = u;
			dfs(v,u);
		}
	}
}
void makep(int u,int pre) {
	if(l[u] < width) {
		p[u] = rt;
	} else if(l[u] % width == 0) {
		p[u] = t[u];
	} else {
		p[u] = p[t[u]];
	}
	for(int i = 0; i < g[u].size(); ++i) {
		const int v = g[u][i].v;
		if(v != pre) 
			makep(v,u);
	}
}
int lca(int x,int y) {
	while(p[x] != p[y]) {
		if(l[x] > l[y]) 
			x = p[x];
		else 
			y = p[y];
	}
	while(x != y) {
		if(l[x] > l[y])
			x = t[x];
		else 
			y = t[y];
	}
	return x;
}
