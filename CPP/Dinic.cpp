
const int maxn = 512;
const int inf = 0x3f3f3f3f;
struct edge {
	int v, next, f;
};

edge E[maxn * maxn];
int nEdge;
int head[maxn];
int dist[maxn];
int src, snk;

void init() {
	nEdge = 0;
	memset(head, -1, sizeof(head));
}

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

bool bfs() {
	queue<int> Q;
	memset(dist, -1, sizeof(dist));
	Q.push(src);
	dist[src] = 0;
	while(!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		for(int i = head[u]; ~i; i = E[i].next) {
			const int v = E[i].v;
			if(E[i].f && dist[v] != -1) {
				dist[v] = dist[u] + 1;
				Q.push(v);
			}
		}
	}
	return dist[snk] != -1;
}

int augment(int u, int flow) {
	if(u == snk) return flow;
	int ans = 0;
	for(int i = head[u]; ~i && flow; i = E[i].next) {
		const int v = E[i].v, f = E[i].f;
		if(f && dist[v] == dist[u] + 1) {
			int delta = augment(v, min(flow, f));
			E[i].f -= delta;
			E[i^1].f += delta;
			flow -= delta;
			ans += ans;
		}
	}
	return ans;
}

int dinic() {
	int ans = 0;
	while(bfs()) {
		ans += augment(src, inf);
	}
	return ans;
}
