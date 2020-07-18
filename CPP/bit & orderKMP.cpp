const int maxn = 222222;
int a[maxn],b[maxn];
int bit[maxn];
int pa[maxn],pb[maxn];
int next[maxn];
int n,m;
int low[maxn],eq[maxn];
int sum(int i) {
	int ans = 0;
	while(i) {
		ans += bit[i];
		i -= i&-i;
	}
	return ans;
}
void add(int i,int x) {
	while(i <= m) {
		bit[i] += x;
		i += i&-i;
	}
}
void init_arr() {
	memset(bit,0,sizeof(bit));
	for(int i = 1; i <= n; ++i) {
		low[i] = sum(pa[i]-1);
		eq[i] = sum(pa[i]) - low[i];
		add(pa[i],1);
	}
}
int head;
inline void init_bit() {
	memset(bit,0,sizeof(bit));
	head = 1;
}
bool match(int *T,int begin,int x,int n) {
	while(head != begin) 
		add(T[head++],-1);
	int l = sum(x-1), e = sum(x) - l;
	return low[n] == l && eq[n] == e;
}
void getNext() {
	init_bit();
	next[1] = 0;
	add(pa[1],1);
	for(int i = 2,k = 0; i <= n; ++i) {
		while(k > 0 && !match(pa,i-k,pa[i],k+1))
			k = next[k];
		if(match(pa,i-k,pa[i],k+1))
			k++;
		next[i] = k;
		add(pa[i],1);
	}
}
int kmp() {
	int ans = 0;
	init_bit();
	for(int i = 1,k = 0; i <= m; ++i) {
		while(k > 0 && !match(pb,i-k,pb[i],k+1))
			k = next[k];
		if(match(pb,i-k,pb[i],k+1))
			k++;
		if(k == n) {
			++ans;
			k = next[k];
		}
		add(pb[i],1);
	}
	return ans;
}

