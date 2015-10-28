
const int inf = 0x3f3f3f3f;
const int maxn = 100050;

int a[maxn];
int d[maxn];
void LIS(int *num, int n) {
    memset(d, 0x3f, sizeof(d));
    int len = 0;
    for(int i = 0; i < n; ++i) {
        int j = lower_bound(d+1, d+len+1, a[i]) - d;
        len = max(len, j);
        d[j] = a[i];
    }
    return len;
}

void LNDS(int *num, int n)
    memset(d, 0x3f, sizeof(d));
    int len = 0;
    for(int i = 0; i < n; ++i) {
        int j = upper_bound(d+1, d+len+1, a[i]) - d;
        len = max(len, j);
        d[j] = a[i];
    }
    return len;
}
