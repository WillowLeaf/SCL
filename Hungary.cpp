int n,m;
vector<edge> g[maxn];
int from[maxn];
bool visit[maxn];
bool match(int s) {
	for(int i = 0; i < g[s].size(); ++i) {
		int v = g[s][i];
		if(!visit[v]) {
			visit[v] = true;
			if(from[v] == -1 || match(from[v])) {
				from[v] = s;
				return true;
			}
		}
	}
	return false;
}
int hungary() {
	int ans = 0;
	memset(from,-1,sizeof(from));
	for(int i = 0; i < hori.size(); ++i) {
		memset(visit,0,sizeof(visit));
		if(match(i))
			++ans;
	}
	return ans;
}
void init() {
	hori.clear();
	vert.clear();
	for(int i = 0; i < maxn; ++i) {
		g[i].clear();
	}
}
