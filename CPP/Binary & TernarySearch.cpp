const int eps = 1e-8;
int binarySearch(int l,int r,int val) {
	int left = l, right = r, mid;
	while(r - l > eps) {
		mid = (l + r) / 2;
		if(f(mid) > ans) {
			r = mid;
		} else {
			l = mid;
		}
	}
	return (l + r) / 2;
}

double ternarySearch(int l,int r) {
	int left = l, right = r, mid1, mid2;
	while(right - left > eps) {
		mid1 = (left * 2 + right) / 3;
		mid2 = (left + right * 2) / 3;
		if(f(mid1) > f(mid2)) {
			left = mid1;
		} else {
			right = mid2;
		}
	}
	return mid1;
}
