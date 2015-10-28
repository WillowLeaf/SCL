vector<int> g[maxn];
stack<int> S;
bool inStack[maxn];
int color[maxn];
int nColor = 0;
int low[maxn],dfn[maxn];
void tarjan(int u)
{
	low[u] = dfn[u] = ++Time;
	S.push(u);
	inStack[u] = true;
	for(int i = 0; i < g[u].size(); ++i) {
		const int v = g[u][i];
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u],low[v]);
		} else if(inStack[v]) low[u] = min(low[u],dfn[v]);
	}
	if(dfn[u] == low[u]) {
		++nColor;
		while(!S.empty() && dfn[S.top()] >= dfn[u]) {
			color[S.top()] = nColor;
			inStack[S.top()] = false;
			S.pop();
		}
	}
}

