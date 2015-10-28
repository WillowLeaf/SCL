typedef unsigned long long ull;
typedef long long ll;

using namespace std;

const int maxn = 2048;
const int inf = 0x3f3f3f3f;
const int superSrc = 2000, superSnk = 2001;
struct edge {
	int v, next, f;
};

edge E[400000];
int nEdge;
int head[maxn];

void addEdge(int u, int v, int f) {
	E[nEdge].v = v;
	E[nEdge].f = f;
	E[nEdge].next = head[u];
	head[u] = nEdge++;
}

void insert(int u, int v, int f) {
	addEdge(u, v, f);
	addEdge(v, u, 0);
}

bool vis[maxn];
int dist[maxn];
bool bfs(int src, int snk) {
	queue<int> Q;
	memset(dist, -1, sizeof(dist));
	Q.push(src);
	dist[src] = 0;
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for(int i = head[u]; ~i; i = E[i].next) {
			int v = E[i].v;
			if(dist[v] == -1 && E[i].f) {
				dist[v] = dist[u] + 1;
				Q.push(v);
				if(v == snk) {
					return true;
				}
			}
		}
	}
	return false; 
}

int augment(int u, int snk, int flow) {
	if(u == snk) return flow;
	int ans = 0;
	for(int i = head[u]; ~i && flow; i = E[i].next) {
		const int v = E[i].v, f = E[i].f;
		if(f && dist[v] == dist[u] + 1) {
			int delta = augment(v, snk, min(flow, f));
			E[i].f -= delta;
			E[i^1].f += delta;
			flow -= delta;
			ans += delta;
		}
	}
	return ans;
}

int dinic(int src, int snk) {
	int ans = 0;
	while(bfs(src, snk)) {
		ans += augment(src, snk, inf);
	}
	return ans;
}


int M[maxn];

void init() {
	nEdge = 0;
	memset(head, -1,sizeof(head));
	memset(M, 0, sizeof(M));
}

int low[100000];
int main() {
	int n, m;
	while(~scanf("%d%d", &n, &m)) {
		int src = n + m + 1, snk = n + m + 2;
		init();
		for(int i = 1; i <= m; ++i) {
			int G;
			scanf("%d", &G);
			//insert(n + i, snk, inf);
			M[n + i] += G;
			M[snk] -= G;
		}
		int tmpD[maxn];
		int cnt = 0;
		for(int i = 1; i <= n; ++i) {
			int C, D;
			scanf("%d%d", &C, &D);
			tmpD[i] = D;
			//insert(src, i, D);
			for(int j = 0; j < C; ++j) {
				int t, l, r;
				scanf("%d%d%d", &t, &l, &r);
				++t;
				insert(i, t + n, r - l);
				low[cnt++] = l;
				M[i] += l;
				M[t + n] -= l;
			}
		}
		for(int i = 1; i <= n; ++i) {
			insert(src, i, tmpD[i]);
		}
		for(int i = 1; i <= m; ++i) {
			insert(n + i, snk, inf);
		}
		int tmp = 0;

		for(int i = 1; i <= snk; ++i) {
			if(M[i] < 0) {
				insert(superSrc, i, -M[i]);
				tmp += -M[i];
			} else if(M[i] > 0) {
				insert(i, superSnk, M[i]);
			}
		}
		insert(snk, src, inf);
		if(dinic(superSrc, superSnk) != tmp) {
			printf("-1\n"); 
		} else {
			printf("%d\n", dinic(src, snk));
			for(int i = 0; i < cnt; ++i) {
				printf("%d\n", E[(i * 2) ^ 1].f + low[i]);
			}
		}
		puts("");
	}
	return 0;
}
