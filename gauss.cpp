double m[maxn][maxn];
bool l[maxn];
double ans[maxn];
int gauss(double (&m)[maxn][maxn],bool (&l)[maxn],double (&ans)[maxn],int n) {
	memset(l,0,sizeof(l));
	for(int i = 0; i < maxn; ++i) ans[i] = 0;
	int r = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = r; j < n; ++j) {
			if(fabs(m[j][i]) > eps) {
				for(int k = i; k < n+1; ++k) 
					swap(m[r][k],m[j][k]);
				break;
			}
		}
		if(fabs(m[r][i]) <= eps) 
			continue;
		for(int j = 0; j < n; ++j) {
			if(j != r && fabs(m[j][i]) > eps) {
				double mu = m[j][i] / m[r][i];
				for(int k = i; k <= n; ++k) 
					m[j][k] -= mu * m[r][k];
			}
		}
		++r; l[i] = true;
	}
	for(int i = 0; i < n; ++i) {
		if(l[i]) {
			for(int j = 0; j < n; ++j) {
				if(fabs(m[j][i]) > eps) 
					ans[i] = m[j][n] / m[j][i];
			}
		}
	}
	return r;
}
