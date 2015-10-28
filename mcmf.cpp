const int maxn = 256;
const int maxe = 256 * 256;
int src,snk;

struct Edge{
	int v,next,f,w;
	Edge() {}
	Edge(int vv,int nn,int ff,int ww): v(vv),next(nn),f(ff),w(ww) {}
};
Edge e[maxe];
int g[maxn];
int cnt;
void init() {
	cnt = 0;
	memset(g,-1,sizeof(g));
}

void addEdge(int u,int v,int f,int w) {
	e[cnt] = Edge(v,g[u],f,w);
	g[u] = cnt++;
	e[cnt] = Edge(u,g[v],0,-w);
	g[v] = cnt++;
}
int dist[maxn];
bool inQ[maxn];
int prev[maxn],pree[maxe];
bool findPath() {
	memset(inQ,0,sizeof(inQ));
	for(int i = 0; i < maxn; ++i) dist[i] = inf;
	queue<int> Q;
	Q.push(src);
	dist[src] = 0;
	inQ[src] = true;
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for(int i = g[u]; ~i; i = e[i].next) {
			int v = e[i].v;
			if(e[i].f && dist[v] > dist[u] + e[i].w) {
				dist[v] = dist[u] + e[i].w;
				pree[v] = i;
				prev[v] = u;
				if(!inQ[v]) {
					inQ[v] = true;
					Q.push(v);
				}
			}
		}
		inQ[u] = false;
	}
	return dist[snk] < inf;
}

int augment() {
	int u = snk;
	int dd = inf;
	while(u != src) {
		dd = min(dd,e[pree[u]].f);
		u = prev[u];
	}
	u = snk;
	while(u != src) {
		e[pree[u]].f -= dd;
		e[pree[u]^1].f += dd;
		u = prev[u];
	}
	return dd * dist[snk];
}
int mcmf() {
	int ans = 0;
	while(findPath()) {
		ans += augment();
	}
	return ans;
}
int N,M;
inline int getDist(const point& a,const point& b) {
	const int dx = a.first-b.first;
	const int dy = a.second-b.second;
	return (dx>0?dx:-dx) + (dy>0?dy:-dy);
}
