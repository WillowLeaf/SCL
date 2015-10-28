const int maxn = 100050;
const int inf = 0x3f3f3f3f;


char str[maxn];

struct State {
	State *go[26], *par;
	int val, tmp, ans;
} statePool[maxn * 2];
int sCnt;

inline State *newState(int val) {
	memset(statePool[sCnt].go, 0, sizeof(statePool[sCnt].go));
	statePool[sCnt].par = 0;
	statePool[sCnt].val = val;
	statePool[sCnt].tmp = 0; 
	statePool[sCnt].ans = inf;
	return &statePool[sCnt++];
}

State *root, *last;
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

int cnt[maxn];
State *buff[maxn * 2];
State *sorted[maxn * 2];

void cntSort(int n) {
	for(int i = 0; i < n; ++i) buff[i] = sorted[i];
	for(int i = 0; i < maxn; ++i) cnt[i] = 0;
	for(int i = 0; i < n; ++i) ++cnt[buff[i]->val];
	for(int i = 1; i < maxn; ++i) cnt[i] += cnt[i-1];
	for(int i = n - 1; i >= 0; --i) sorted[--cnt[buff[i]->val]] = buff[i];
}

int main() {
	scanf("%s", str);
	last = root = newState(0);
	for(int i = 0; str[i]; ++i) {
		extend(str[i] - 'a');
	}
	for(int i = 0; i < sCnt; ++i) {
		sorted[i] = statePool + i;
	}
	cntSort(sCnt);
	while(~scanf("%s", str)) {
		State *iter = root;
		int cnt = 0;
		for(int i = 0; str[i]; ++i) {
			int x = str[i] - 'a';
			if(iter->go[x]) {
				iter = iter->go[x];
				iter->tmp = max(iter->tmp, ++cnt);
			} else {
				while(iter != root && !iter->go[x]) {
					iter = iter->par;
					cnt = iter->val;
				}
				if(iter->go[x]) {
					iter = iter->go[x];
					iter->tmp = max(iter->tmp, ++cnt);
				}
			}
		}
		for(int i = sCnt-1; i >= 0; --i) {
			State *cur = sorted[i];
			cur->ans = min(cur->ans, cur->tmp);
			if(cur->par) cur->par->tmp = max(cur->par->tmp, min(cur->par->val, cur->tmp));
			cur->tmp = 0;
		}
	}
	int ret = 0;
	for(int i = 0; i < sCnt; ++i) {
		ret = max(ret, sorted[i]->ans);
	}
	printf("%d\n", ret);
}
