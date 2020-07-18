#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

const int maxn = 100000;
const int maxe = 10000;
const int inf = 0x3f3f3f3f;

struct edge {
	int v,f,next;
};
edge e[maxe];
int g[maxn];
int dist[maxn];
int ecnt;
int L[256][32];
int U[256][32];
int mat[256][32];
int tot_in[32];
int tot_out[256];
int rsum, csum;
void init() {
	ecnt = 0;
	rsum = csum = 0;
	memset(g,-1,sizeof(g));
	memset(L,0,sizeof(L));
	memset(U,63,sizeof(U));
	memset(tot_in,0,sizeof(tot_in));
	memset(tot_out,0,sizeof(tot_out));
}
void addEdge(int u,int v,int f) {
	e[ecnt].v = v;
	e[ecnt].f = f;
	e[ecnt].next = g[u];
	g[u] = ecnt++;
}
void insert(int u,int v,int f) {
	addEdge(u,v,f);
	addEdge(v,u,0);
}

bool bfs(int src,int snk) {
	memset(dist,-1,sizeof(dist));
	queue<int> Q;
	Q.push(src);
	dist[src] = 0;
	while(!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		for(int i = g[u]; ~i; i = e[i].next) {
			const int v = e[i].v;
			if(e[i].f && dist[v] == -1) {
				dist[v] = dist[u] + 1;
				Q.push(v);
			}
		}
	}
	return ~dist[snk];
}

int augment(int u,int snk,int flow) {
	if(u == snk) 
		return flow;
	int ans = 0;
	for(int i = g[u]; ~i && flow; i = e[i].next) {
		const int v = e[i].v;
		if(e[i].f && dist[v] == dist[u] + 1) {
			int dd = augment(v,snk,min(flow,e[i].f));
			ans += dd;
			flow -= dd;
			e[i].f -= dd;
			e[i^1].f += dd;
		}
	}
	return ans;
}
int dinic(int src,int snk) {
	int ans = 0;
	while(bfs(src,snk)) {
		ans += augment(src,snk,inf);
	}
	return ans;
}
void build(int src,int snk,int superSrc,int superSnk,int n, int m) {
	insert(snk,src,inf);
	for(int i = 0; i < n; ++i) {
		int tmp;
		scanf("%d", &tmp);
		rsum += tmp;
		insert(src, i, tmp);
	}
	for(int j = 0; j < m; ++j) {
		int tmp;
		scanf("%d", &tmp);
		csum += tmp;
		insert(n+j, snk, tmp);
	}
	///////////////////
	int C;
	scanf("%d",&C);
	while(C--) {
		int r, c, v;
		char ch[2];
		scanf("%d%d%s%d",&r,&c,ch,&v);
		if(r == 0 && c == 0) {
			for(int i = 0; i < n; ++i) {
				for(int j = 0; j < m; ++j) {
					switch(ch[0]) {
						case '<' :
							U[i][j] = min(U[i][j],v-1);
							break;
						case '=':
							U[i][j] = L[i][j] = v;
							break;
						case '>':
							L[i][j] = max(L[i][j],v+1);
							break;
					}
				}
			}
		} else if(r == 0) {
			c--;
			for(int i = 0; i < n; ++i) {
					switch(ch[0]) {
						case '<' :
							U[i][c] = min(U[i][c],v-1);
							break;
						case '=':
							U[i][c] = L[i][c] = v;
							break;
						case '>':
							L[i][c] = max(L[i][c],v+1);
							break;
					}
			}
		} else if(c == 0) {
			r--;
			for(int j = 0; j < m; ++j) {
					switch(ch[0]) {
						case '<' :
							U[r][j] = min(U[r][j],v-1);
							break;
						case '=':
							U[r][j] = L[r][j] = v;
							break;
						case '>':
							L[r][j] = max(L[r][j],v+1);
							break;
					}
			}
		} else {
			r--; 
			c--;
			switch(ch[0]) {
				case '<' :
					U[r][c] = min(U[r][c],v-1);
					break;
				case '=':
					U[r][c] = L[r][c] = v;
					break;
				case '>':
					L[r][c] = max(L[r][c],v+1);
					break;
			}
		}
	}
	////////////////////////////////////
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			insert(i,n+j,U[i][j] - L[i][j]);
			tot_out[i] += L[i][j];
			tot_in[j] += L[i][j];
		}
	}
	///////////////////////////////////
	for(int i = 0;  i < n; ++i) {
		insert(i,superSnk,tot_out[i]);
	}
	for(int j = 0; j < m; ++j) {
		insert(superSrc,n+j,tot_in[j]);
	}
	//////////////////////////////////
}

bool solve(int src,int snk,int superSrc,int superSnk,int n,int m) {
	if(rsum != csum) return false;
	int tmp = 0;
	for(int j = 0; j < m; ++j) {
		tmp += tot_in[j];
	}
	if(dinic(superSrc,superSnk) != tmp) {
		return false;
	}
	e[0].f = e[1].f = 0;
	dinic(src,snk);
	for(int i = g[src]; ~i; i = e[i].next) {
		if(e[i].v != superSrc && e[i].f) return false;
	}
	for(int i = 0; i < n; ++i) {
		for(int j = g[i]; ~j; j = e[j].next) {
			int v = e[j].v;
			if(v < n + m && v >= n) {
				v -= n;
				mat[i][v] = e[j^1].f + L[i][v];
			}
		}
	}
	return true;
}
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		init();
		int n,m;
		scanf("%d%d",&n,&m);
		int src = n + m,
			snk = n + m + 1,
			superSrc = n + m + 2,
			superSnk = n + m + 3;
		build(src,snk,superSrc,superSnk,n,m);
		bool res = solve(src,snk,superSrc,superSnk,n,m);
		if(res) {
			for(int i = 0; i < n; ++i) {
				for(int j = 0; j < m; ++j) {
					printf("%d",mat[i][j]);
					putchar(j == m-1 ? '\n' : ' ');
				}
			}
		} else {
			printf("IMPOSSIBLE\n");
		}
	}
}

