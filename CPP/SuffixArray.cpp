const int maxn = 5000050;
const int inf = 0x3f3f3f3f;
int cnt[maxn];

int buff1[maxn], buff2[maxn], buff3[maxn];

void cntSort(int *in, int *out, int *key, int n, int m) {
	for(int i = 0; i <= m; ++i) cnt[i] = 0;
	for(int i = 0; i < n; ++i) ++cnt[key[i]];
	for(int i = 1; i <= m; ++i) cnt[i] += cnt[i-1];
	for(int i = n-1; i >= 0; --i) out[--cnt[key[i]]] = in[i];
}

void DA(int *sa, int *T, int n, int m) {
	int *rank = buff1, *temp = buff2;
	for(int i = 0; i < n; ++i) temp[i] = i;
	cntSort(temp, sa, T, n, m);
	rank[sa[0]] = 0;
	for(int i = 1; i < n; ++i) rank[sa[i]] = rank[sa[i-1]] + (T[sa[i]] == T[sa[i-1]] ? 0 : 1);
	for(int mxRank = rank[sa[n-1]], l = 1; mxRank < n-1; l *= 2, mxRank = rank[sa[n-1]]) {
		int p = 0;
		for(int i = n - l; i < n; ++i) temp[p++] = i;
		for(int i = 0; i < n; ++i) if(sa[i] >= l) temp[p++] = sa[i] - l;
		for(int i = 0; i < n; ++i) buff3[i] = rank[temp[i]];
		cntSort(temp, sa, buff3, n, mxRank);
		swap(rank, temp);
		rank[sa[0]] = 0;
		for(int i = 1; i < n; ++i) rank[sa[i]] = rank[sa[i-1]] + ((temp[sa[i-1]] == temp[sa[i]] && temp[sa[i-1]+l] == temp[sa[i]+l]) ? 0 : 1);
	}
}

void make(int *height, int *rank, int *sa, int *T, int n) {
	for(int i = 0; i <= n; ++i) rank[sa[i]] = i;
	int k = 0;
	for(int i = 0; i < n; ++i) {
		if(k) k--;
		for(int j = sa[rank[i]-1]; T[i + k] == T[j + k]; ++k);
		height[rank[i]] = k;
	}
}

char str[2000050];
int T[maxn];
int sa[maxn], height[maxn], rank[maxn];

////////////////////////////////////////////
//divide height array into segments
int len = 0;
int delim = 0;

bool check(int k) {
	int mn = inf, mx = -1;
	for(int i = 1; i <= len; ++i) {
		if(height[i] < k) {
			mn = sa[i], mx = sa[i];
		} else {
			mx = max(mx, sa[i]);
			mn = min(mn, sa[i]);
			if(mx > delim && mn < delim) {
				return true;
			}
		}
	}
	return false;
}

//////////////////////////////////////////////////
//ST algorithm
void init() {
    for(int i = 0; i < maxn; ++i) {
        logn[i] = floor(log2(i));
    }
}

void makeDp(int dp[][32], int num[], int n) {
    for(int i = 1; i <= n; ++i) {
        dp[i][0] = num[i];
    }
    for(int j = 1;  (1 << j) <= n; ++j) {
        for(int i = 1; i + (1 << j) - 1 <= n; ++i) {
            dp[i][j] = min(dp[i][j-1], dp[i + (1 << (j-1))][j-1]);
        }
    }
}

inline int getMin(int dp[][32], int l, int r) {
    int j = logn[r-l+1];
    return min(dp[l][j], dp[r - (1 << j) + 1][j]);
}

inline int lcp(int dp[][32], int l, int r) {
    if(l == r) {
        return len - l;
    } else  {
        int a = rank[l], b = rank[r];
        if(a > b) swap(a,b);
        return getMin(dp, a+1, b);
    }
}

//////////////////////////////////////////////

//preprocess out the number of substr
void process() {
    for(int i = 1; i <= len; ++i) {
        num[i] = len - sa[i] - height[i];
    }
    for(int i = 2; i <= len; ++i) {
        num[i] += num[i-1];
    }
}

//binary search the end of consecutive appearence
int bin(int l, int r, int length) {
    int left = l, right = r, mid, ans = -1;
    int pos = l;
    while(left <= right) {
        mid = (left + right) >> 1;
        if(lcp(sa[pos], sa[mid]) >= length) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}
void calc(ll k, int *l, int *r) {
    num[0] = 0;
    int bg = lower_bound(num + 1, num + len, k) - num;
    int length = height[bg] + (k - num[bg-1]); //length of the kth substr x
	//find the last appearence of x
	//(they must appear in height consecutively
    int ed = bin(bg, len, length);	
	//get the lexicologically smallest one
	int pos = getMin(dp2, bg, ed);
    *l = pos + 1;
    *r = pos + length - 1 + 1;

}
