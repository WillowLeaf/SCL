void tarjan(int u) {
	low[u] = dfn[u] = ++Time;
	for(int i = head[u]; ~i; i = e[i].next) {
		const int v = e[i].v;
		if(dfn[v] == -1) {
			type[i] = type[i^1]= 't';
			S.push(i);
			tarjan(v);
			low[u] = min(low[u],low[v]);
			if(low[v] >= dfn[u]) {
				++nBCC;
				while(!S.empty() && dfn[e[S.top()].u] >= dfn[v]) {
					bcc[S.top()] = nBCC;
					bcc[S.top()^1] = nBCC;
					S.pop();
					++cnt[nBCC];
				}
				bcc[S.top()] = nBCC;	//pop (u,v)
				bcc[S.top()^1] = nBCC;
				S.pop();
				++cnt[nBCC];
			}
		} else if(!type[i]) {
			type[i] = type[i^1] = 'b';
			S.push(i);
			low[u] = min(low[u],dfn[v]);
		}
	}
}
bool isODD(int u,int c,int b) {
	if(color[u]) {
		if(color[u] != c) return true;
		else return false;
	}
	color[u] = c;
	for(int i = head[u]; ~i; i = e[i].next) {
		if(bcc[i] != b || type[i]) continue;
		type[i] = type[i^1] = 'x';
		if(isODD(e[i].v,-c,b))
			return true;
	}
	return false;
}
