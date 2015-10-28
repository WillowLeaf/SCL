vector<int> g[maxn];
int sorted[maxn];
int color[maxn];
int pos;
bool dfs(int u) {
	color[u] = 1;
	for(int i = 0; i < g[u].size(); ++i) {
		const int v = g[u][i];
		if(color[v] == 1) {			//grey
			return false;
		} else if(color[v] == 0) {	//white
			if(!dfs(v)) return false;
		}
	}
	sorted[pos--] = u;
	color[u] = 2;
	return true;
}
bool topoSort() {
	for(int i = 1; i <= n; ++i) {
		if(!color[i] && dfs(i) == false) return false;
	}
	return true;
}
void init_topo() {
	pos = n - 1;
	memset(color, 0, sizeof(color));
	for(int i = 0; i < maxn; ++i) {
		g[i].clear();
	}
}
