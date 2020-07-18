char P[10050];
char T[1000050];

const int maxn = 100050;
int next[maxn];
void getNext(int len)
{
	next[1] = 0;
	for(int i = 2, k = 0; i <= len; ++i) {
		while(k > 0 && P[i-1] != P[k]) {
			k = next[k];
		}
		if(P[i-1] == P[k]) {
			++k;
		}
		next[i] = k;
	}
}
int main()
{
	int nCase;
	scanf("%d", &nCase);
	while(nCase--) {
		int ans = 0;
		scanf("%s", P);
		scanf("%s", T);
		int len = strlen(P);
		int lenT = strlen(T);
		getNext(len);
		for(int i = 0, k = 0; i < lenT; ++i) {
			while(k > 0 && T[i] != P[k]) {
				k = next[k];
			}
			if(T[i] == P[k]) {
				++k;
			}
			if(k == len) {
				++ans;
				k = next[k];
			}
		}
		printf("%d\n", ans);
	}
}
