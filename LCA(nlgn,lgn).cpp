
const int maxn = 40050;
const int inf = 0x3f3f3f3f;

struct edge{
	int v,w;
	edge(int vv,int ww):v(vv),w(ww) {}
};
vector<edge> g[maxn];
int l[maxn],t[maxn],dist[maxn];
int N,M,rt;
int dp[maxn][32];
void init() {
	for(int i = 0; i < maxn; ++i) 
		g[i].clear();
}
void dfs(int u,int fa) {
	for(int i = 0; i < g[u].size(); ++i) {
		const int v = g[u][i].v, w = g[u][i].w;
		if(v == fa) continue;
		l[v] = l[u] + 1;
		dist[v] = dist[u] + w;
		t[v] = u;
		dfs(v,u);
	}
}

void preprocess() {
	memset(dp,-1,sizeof(dp));
	for(int i = 1; i <= N; ++i) 
		dp[i][0] = t[i];
	for(int j = 1; 1 << j < N; ++j) 
		for(int i = 1; i <= N; ++i) 
			dp[i][j] = dp[dp[i][j-1]][j-1];
}
int lca(int x,int y) {
	if(l[x] < l[y]) swap(x,y);
	int log = 0;
	for(log = 0; 1<<log <= l[x]; ++log);
	--log;
	for(int i = log; i >= 0; --i) {
		if(l[x]-(1<<i) >= l[y]) {
			x = dp[x][i];
		}
	}
	if(x == y)
		return x;
	for(int i = log; i >= 0; --i) {
		if(dp[x][i] != -1 && dp[x][i] != dp[y][i]) {
			x = dp[x][i];
		}
	}
	return t[x];
}
