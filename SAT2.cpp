const int maxn = 128;
int degree[maxn],conflict[maxn],dfn[maxn],low[maxn],belong[maxn],timeStamp,nSCC;
vector<int> scc[maxn] , g[maxn];
stack<int> S;
bool inS[maxn];
int color[maxn];
void init() {
	memset(dfn,0,sizeof(dfn));
	memset(color,0,sizeof(color));
	memset(inS,0,sizeof(inS));
	nSCC = timeStamp = 0;
	for(int i = 0; i < maxn; ++i) g[i].clear();
	for(int i = 0; i < maxn; ++i) scc[i].clear();
	while(!S.empty()) S.pop();
}
void tarjan(int u) {
	low[u] = dfn[u] = ++timeStamp;
	S.push(u);
	inS[u] = true;
	for(int i = 0; i < g[u].size(); ++i) {
		const int v = g[u][i];
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u],low[v]);
		} else if(inS[v]) low[u] = min(low[u],dfn[v]);
	}
	if(dfn[u] == low[u]) {
		nSCC++;
		while(!S.empty() && dfn[S.top()] >= dfn[u]) {
			belong[S.top()] = nSCC;
			inS[S.top()] = false;
			S.pop();
		}
	}
}
int n,m;
void build() {
	for(int u = 0; u < 2*n; ++u) {
		for(int i = 0; i < g[u].size(); ++i) {
			const int v = g[u][i];
			if(belong[u] != belong[v]) 
				scc[belong[v]].push_back(belong[u]);
		}
	}
}

void colorDFS(int u) {
	if(color[u]) return;
	color[u] = 2;
	for(int i = 0; i < scc[u].size(); ++i) 
		colorDFS(scc[u][i]);
}
void TopoSort() {
	queue<int> Q;
	memset(degree,0,sizeof(degree));
	for(int i = 1; i <= nSCC; ++i) 
		for(int j = 0; j < scc[i].size(); ++j) 
			degree[scc[i][j]]++;
	for(int i = 1; i <= nSCC; ++i) 
		if(!degree[i]) Q.push(i);
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		if(color[u]) continue;
		color[u] = 1;
		colorDFS(conflict[u]);
		for(int i = 0; i < scc[u].size(); ++i) {
			const int v = scc[u][i];
			if(--degree[v] == 0) Q.push(v);
		}
	}
}

void encolor()
{
	for(int i = 0; i < 2*n; ++i) 
		conflict[belong[i]] = belong[i^1];
	TopoSort();
}
int main() {
	int x,y;
	char c1,c2;
	while(scanf("%d%d",&n,&m),n||m) {
		init();
		for(int i = 0; i < m; ++i) {
			scanf("%d%c %d%c",&x,&c1,&y,&c2);
			int n1 = (c1 == 'h' ? 1:0) + 2*x;
			int n2 = (c2 == 'h' ? 1:0) + 2*y;
			g[n1].push_back(n2^1);
			g[n2].push_back(n1^1);
		}
		g[0].push_back(1);
		for(int i = 0; i < 2*n; ++i) 
			if(!dfn[i]) tarjan(i);
		for(int i = 0; i < 2*n; i += 2) 
			if(belong[i] == belong[i+1]) {
				printf("bad luck\n");
				goto next;
			}
		build();
		encolor();
		for(int i = 1; i < n; ++i) {
			if(color[belong[i*2]] == color[belong[0]]) {
				printf("%dw ",i);
			} else {
				printf("%dh ",i);
			}
		}
next:;
	}
}
