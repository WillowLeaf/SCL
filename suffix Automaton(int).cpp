struct State{
	int go[26], par;
	int val;
} S[4 * maxn];
int sCnt;

int newState(int arg) {
	memset(S[sCnt].go, -1, sizeof(S[sCnt].go));
	S[sCnt].par = -1;
	S[sCnt].val = arg;
	return sCnt++;
}

int root = 0, last = 0;
void extend(int x) {
	int p = last;
	int np = newState(S[p].val + 1);
	while(p != -1 && S[p].go[x] == -1) {
		S[p].go[x] = np;
		p = S[p].par; 
	}
	if(p == -1) {
		S[np].par = root;
	} else {
		int q = S[p].go[x];
		if(S[p].val + 1 == S[q].val) {
			S[np].par = q;
		} else {
			int nq = newState(S[p].val + 1);
			memcpy(S[nq].go, S[q].go, sizeof(S[nq].go));
			S[nq].par = S[q].par;
			S[q].par = nq;
			S[np].par = nq;
			while(p != -1 && S[p].go[x] == q) {
				S[p].go[x] = nq;
				p = S[p].par;
			}
		}
	}
	last = np;
}



