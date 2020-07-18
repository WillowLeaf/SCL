int factor(int n,int a[],int b[])
{
	int tot = 0;
	int tmp = (int)(sqrt(n) + 1);
	int cur = n;
	for(int i = 2; i <= tmp; ++i) 
		if(cur%i == 0) {
			a[tot] = i;
			b[tot] = 0;
			while(cur%i==0) {
				cur /= i;
				++b[tot];
			}
			++tot;
		}
	if(cur != 1) {
		a[tot] = cur;
		b[tot] = 1;
		++tot;
	}
	return tot;
}


int phi(int n) {
	int s = n;
	int ans = n;
	for(int i = 2; i*i <= n; ++i) {
		if(s % i == 0) {
			ans -= ans / i;
			while(s % i == 0) s /= i;
		}
	}
	if(s > 1) {
		ans -= ans / s;
	}
	return ans;
}
