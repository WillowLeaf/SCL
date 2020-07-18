const int maxn = 4096,inf = 0x3f3f3f3f;
int cnt[maxn];
int buff1[maxn],buff2[maxn],buff3[maxn];

void CntSort(int in[],int out[],int key[],int n,int m) {
	for(int i = 0; i < m; ++i) cnt[i] = 0;
	for(int i = 0; i < n; ++i) cnt[key[i]]++;
	for(int i = 1; i < m; ++i) cnt[i] += cnt[i-1];
	for(int i = n-1; i >= 0; --i) out[--cnt[key[i]]] = in[i];
}
void DA(int sa[],int T[],int n,int m) {
	int *temp = buff1, *rank = buff2;
	for(int i = 0; i < n; ++i) temp[i] = i;
	CntSort(temp,sa,T,n,m);
	rank[sa[0]] = 0;
	for(int i = 1; i < n; ++i) rank[sa[i]] = rank[sa[i-1]] + (T[sa[i]] != T[sa[i-1]] ? 1:0);
	for(int mxRnk = rank[sa[n-1]], l = 1; mxRnk < n-1; mxRnk = rank[sa[n-1]], l *= 2) {
		int p = 0;
		for(int i = n-l; i < n; ++i) temp[p++] = i;
		for(int i = 0; i < n; ++i) if(sa[i] >= l) temp[p++] = sa[i] - l;
		for(int i = 0; i < n; ++i) buff3[i] = rank[temp[i]];
		CntSort(temp,sa,buff3,n,mxRnk+1);
		swap(rank,temp);
		rank[sa[0]] = 0;
		for(int i = 1; i < n; ++i) rank[sa[i]] = rank[sa[i-1]] + ((temp[sa[i-1]] != temp[sa[i]] || temp[sa[i-1]+l] != temp[sa[i]+l]) ? 1 : 0);
	}
}
void makeHeight(int height[],int T[],int sa[],int n) {
	int *rank = buff1, k = 0;
	for(int i = 1; i <= n; ++i) rank[sa[i]] = i;
	for(int i = 0; i < n; ++i) {
		if(k) k--;
		for(int j = sa[rank[i]-1]; T[j+k] == T[i+k]; ++k);
		height[rank[i]] = k;
	}
}
int sa[maxn],height[maxn],T[maxn];
int dp[maxn][16];
void preprocess(int len) {
	for(int i = 1; i <= len; ++i) dp[i][0] = i;
	for(int j = 1; (1<<j) <= len; ++j) {
		for(int i = 1; i <= len; ++i) {
			int a = dp[i][j-1], b = dp[i+(1<<j-1)][j-1];
			dp[i][j] = (height[a] < height[b] ? a : b);
		}
	}
}
int rmq(int x,int y) {
	if(x > y) swap(x,y);
	++x;
	int l = log(y-x+1.0) / log(2.0) + 1e-6;
	int a = dp[x][l], b = dp[y-(1<<l)+1][l];
	return (height[a] < height[b] ? a : b);
}


inline int check(int i,int len) {
	int *rank = buff1;
	int odd = height[rmq(rank[i],rank[len-i-1])];
	int even = (i ? height[rmq(rank[i],rank[len-i])] : -1);
	return max(2*odd-1,2*even);
}
int main() {
	string s;
	cin >> s;
	int len = 0;
	for(int i = 0; i < s.size(); ++i) T[len++] = s[i];
	T[len++] = '$';
	for(int i = s.size()-1; i >= 0; --i) T[len++] = s[i];
	T[len] = 0;
	DA(sa,T,len+1,128);
	makeHeight(height,T,sa,len);
	preprocess(len);
	int ans = -1, mx = 0;
	for(int i = 0; i < s.size(); ++i) {
		int t = check(i,len);
		if(t > mx) {mx = t; ans = i;}
	}
	ans -= (mx / 2);
	for(int i = 0; i < mx; ++i) {
		cout << s[ans + i];
	}
	cout << endl;
}
