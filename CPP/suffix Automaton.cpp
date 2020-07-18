const int maxn = 250050;

//////////////////////////////
struct State{
	State *go[26], *par;
	int val;
} S[maxn * 2];
int sCnt;

State *newState(int arg) {
	memset(S[sCnt].go, 0, sizeof(S[sCnt].go));
	S[sCnt].par = 0;
	S[sCnt].val = arg;
	return &S[sCnt++];
}

State *root = 0, *last = 0;
void extend(int x) {
	State *p = last;
	State *np = newState(p->val + 1);
	while(p && !p->go[x]) {
		p->go[x] = np;
		p = p->par; 
	}
	if(!p) {
		np->par = root;
	} else {
		State *q = p->go[x];
		if(p->val + 1 == q->val) {
			np->par = q;
		} else {
			State *nq = newState(p->val + 1);
			memcpy(nq->go, q->go, sizeof(nq->go));
			nq->par = q->par;
			q->par = nq;
			np->par = nq;
			while(p && p->go[x] == q) {
				p->go[x] = nq;
				p = p->par;
			}
		}
	}
	last = np;
}


//////////////////////////////
char T1[maxn];
char T2[maxn];
int l1, l2;
int solve() {
	int ans = 0;
	State *cur = root;
	int cnt = 0;
	for(int i = 0; i < l2; ++i) {
		int ch = T2[i] - 'a';
		if(cur->go[ch]) {
			cur = cur->go[ch];
			ans = max(ans, ++cnt);
		} else {
			while(cur != root && cur->go[ch] == 0) {
				cur = cur->par;
				cnt = cur->val;
			}
			if(cur->go[ch]) {
				cur = cur->go[ch];
				ans = max(ans, ++cnt);
			}
		}
	}
	return ans;
}

int main() {
	scanf("%s", T1);
	scanf("%s", T2);
	l1 = strlen(T1);
	l2 = strlen(T2);
	last = root = newState(0);
	for(int i = 0; i < l1; ++i) {
		extend(T1[i]-'a');
	}
	printf("%d\n", solve());
}
