
struct matrix
{
	int m[maxm][maxm];
	int nr,nc;
	matrix(int r,int c):nr(r),nc(c) {}
};

matrix operator*(const matrix& a,const matrix& b)
{
	matrix res(a.nr,b.nc);
	for(int i = 0; i < res.nr; ++i) {
		for(int j = 0; j < res.nc; ++j) {
			res.m[i][j] = 0;
			for(int k = 0; k < a.nc; ++k) {
				res.m[i][j] = (res.m[i][j] + (a.m[i][k] * b.m[k][j]) % mod) % mod;
			}
		}
	}
	return res;
}

matrix qPower(const matrix a,int p)
{
	matrix t = a;
	matrix res(a.nr,a.nc);
	for(int i = 0; i < res.nr; ++i) {
		for(int j = 0; j < res.nc; ++j) {
			res.m[i][j] = (i == j ? 1 : 0);
		}
	}
	while(p) {
		if(p & 1) 
			res = res * t;
		p >>= 1;
		t = t * t;
	}
	return res;
}


