#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int maxn = 40050;
const int inf = 0x3f3f3f3f;


int N,M,rt,cur;
struct edge{
	int v,w;
	edge(int vv,int ww):v(vv),w(ww) {}
};
vector<edge> g[maxn];
int l[maxn],t[maxn],dist[maxn],eular[maxn<<1],first[maxn];
int dp[maxn<<1][32];
void init() {
	for(int i = 0; i < maxn; ++i) 
		g[i].clear();
	cur = 0;
}
void dfs(int u,int fa) {
	eular[++cur] = u;
	first[u] = cur;
	for(int i = 0; i < g[u].size(); ++i) {
		const int v = g[u][i].v, w = g[u][i].w;
		if(v == fa) continue;
		l[v] = l[u] + 1;
		dist[v] = dist[u] + w;
		t[v] = u;
		dfs(v,u);
		eular[++cur] = u;
	}
}

void preprocess() {
	const int bound = 2*N-1;
	for(int i = 1; i <= bound; ++i) 
		dp[i][0] = eular[i];
	for(int j = 1; 1<<j <= bound; ++j) 
		for(int i = 1; i + (1<<j) - 1 <= bound; ++i) {
			int a = dp[i][j-1];
			int b = dp[i+(1<<j-1)][j-1];
			dp[i][j] = (l[a]<l[b] ? a:b);
		}
}
inline int rmq(int x,int y) {
	int k = log(y-x+1.0) / log(2.0);
	int a = dp[x][k];
	int b = dp[y-(1<<k)+1][k];
	return (l[a]<l[b])?a:b;
}
inline int lca(int x,int y) {
	int a = first[x],b = first[y];
	if(a>b) swap(a,b);
	return rmq(a,b);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		init();
		scanf("%d%d",&N,&M);
		int u,v,w;
		for(int i = 0; i < N - 1; ++i) {
			scanf("%d%d%d",&u,&v,&w);
			g[u].push_back(edge(v,w));
			g[v].push_back(edge(u,w));
		}
		rt = rand() % N + 1;
		l[rt] = 1;
		dist[rt] = 0;
		dfs(rt,0);
		preprocess();
		int x,y;
		for(int i = 0; i < M; ++i) {
			scanf("%d%d",&x,&y);
			printf("%d\n",dist[x]+dist[y]-2*dist[lca(x,y)]);
		}
	}
}
