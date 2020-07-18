const int maxe = 1024;
const int maxn = 128;
const int inf = 0x3f3f3f3f;

struct edge {
	int v, f, next;
} E[maxe];
int nEdge;

int head[maxn];

void addEdge(int u, int v, int f) {
	E[nEdge].v = v;
	E[nEdge].f = f;
	E[nEdge].next = head[u];
	head[u] = nEdge++;
	E[nEdge].v = u;
	E[nEdge].f = 0;
	E[nEdge].next = head[v];
	head[v] = nEdge++;
}

int dist[maxn];
bool bfs(int src, int snk) {
	memset(dist, -1, sizeof(dist));
	queue<int> Q;
	dist[src] = 0;
	Q.push(src);
	while(!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		for(int i = head[u]; ~i; i = E[i].next) {
			const int v = E[i].v, f = E[i].f;
			if(f && dist[v] == -1) {
				dist[v] = dist[u] + 1;
				Q.push(v);
			}
		}
	}
	return dist[snk] != -1;
}

int augment(int u, int snk, int flow) {
	if(u == snk) {
		return flow;
	}
	int ans = 0;
	for(int i = head[u]; ~i && flow; i = E[i].next) {
		const int v = E[i].v, f = E[i].f;
		if(f && dist[v] == dist[u] + 1) {
			int delta = augment(v, snk, min(flow, f));
			flow -= delta;
			ans += delta;
			E[i].f -= delta;
			E[i^1].f += delta;
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
	memset(head, -1, sizeof(head));
	memset(M, 0, sizeof(M));
	nEdge = 0;
}

int main() {
	int n, m;
	//freopen("out.txt", "w", stdout);
	while(scanf("%d%d", &n, &m), n || m) {
		init();
		int superSrc = n + 1, superSnk = n + 2, src = n + 3, snk = n + 4;
		char buff[3][4];
		int val[3];
		for(int i = 0; i < m; ++i) {
			scanf("%s%s%s", buff[0], buff[1], buff[2]);
			for(int j = 0; j < 3; ++j) {
				if(buff[j][0] == '+') {
					val[j] = src;
				} else if(buff[j][0] == '-') {
					val[j] = snk;
				} else {
					sscanf(buff[j], "%d", &val[j]);
				}
			}
			addEdge(val[0], val[1], inf - val[2]);
			M[val[0]] += val[2];
			M[val[1]] -= val[2];
		}
		int tot = 0;
		for(int i = 1; i <= snk; ++i) {
			if(M[i] > 0) {
				addEdge(i, superSnk, M[i]);
				tot += M[i];
			} else if(M[i] < 0) {
				addEdge(superSrc, i, -M[i]);
			}
		}
		addEdge(snk, src, inf);
		if(dinic(superSrc, superSnk) != tot) {
			printf("impossible\n");
		} else {
			/*
			int tmp = M[src];
			for(int i = head[src]; ~i; i = E[i].next) {
				if(E[i].v <= n) {
					tmp += E[i^1].f;
				}
			}
			*/
			int tmp = E[nEdge-1].f;
			E[nEdge-1].f = 0;
			E[nEdge-2].f = 0;
			printf("%d\n", tmp - dinic(snk, src));
		}
	}
}

