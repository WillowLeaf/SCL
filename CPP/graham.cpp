const int maxn = 1024;
const double eps = 1e-8;
inline int cmp(double x) {
	if(fabs(x) < eps) return 0;
	else if(x > 0) return 1;
	else return -1;
}
const int STACK_SIZE = 1024;
template <typename T>
struct stack {
	T data[STACK_SIZE];
	int size;
	stack():size(0) {}
	void push(const T& a) {
		data[++size] = a;	
	}
	void pop() {
		--size;
	}
	T top()	{
		return data[size];
	}
	bool empty() {
		return size == 0;
	}
};
struct point {
	double x,y;
	point() {}
	point(double xx,double yy) : x(xx),y(yy) {}
	
	double norm() {
		return sqrt(x*x + y*y);
	}
	friend point operator+(const point& lhs,const point& rhs) {
		return point(lhs.x + rhs.x,lhs.y + rhs.y);
	}
	friend point operator-(const point& lhs,const point& rhs) {
		return point(lhs.x - rhs.x,lhs.y - rhs.y);
	}
	friend point operator*(const point& lhs,const double rhs) {
		return point(lhs.x*rhs,lhs.y*rhs);
	}
	friend point operator*(const double lhs,const point& rhs) {
		return point(lhs*rhs.x,lhs*rhs.y);
	}
	friend double dist(const point& lhs,const point& rhs) {
		return sqrt((lhs.x-rhs.x) * (lhs.x-rhs.x) + (lhs.y-rhs.y) * (lhs.y-rhs.y));
	}
	friend double dotMul(const point& lhs,const point& rhs) {
		return lhs.x*rhs.x + lhs.y*rhs.y;
	}
	friend double crossMul(const point& lhs,const point& rhs) {
		return lhs.x*rhs.y - lhs.y*rhs.x;
	}
};
struct line {
	point a,b;
	line() {};
	line(const point& pa,const point& pb) : a(pa),b(pb) {}
	inline point GetVect() const {
		return b-a;
	}
	inline double length() const { 
		return dist(b,a);
	}
	bool getK(double &k) const {
		if(b.x == a.x) 
			return false;
		k = (b.y-a.y) / (b.x-a.x);
		return true;
	}
	friend inline bool parallel(const line& l1, const line& l2) {
		return crossMul(l1.GetVect(),l2.GetVect()) == 0;
	}
	//not including the coinciding case
	friend bool intersect(const line& l1,const line& l2,point& res) {
		if(parallel(l1,l2)) 
			return false;
		if(min(l1.a.x,l1.b.x) > max(l2.a.x,l2.b.x) || min(l2.a.x,l2.b.x) > max(l1.a.x,l2.b.x) || 
		   min(l1.a.y,l1.b.y) > max(l2.a.y,l1.b.y) || min(l2.a.y,l2.b.y) > max(l1.a.y,l2.b.y))
			return false;
		double p1a = crossMul(l1.GetVect(),l2.a-l1.a),
			   p1b = crossMul(l1.GetVect(),l2.b-l1.a);
		double p2a = crossMul(l2.GetVect(),l1.a-l2.a),
			   p2b = crossMul(l2.GetVect(),l1.b-l2.a);
		if(cmp(p1a*p1b) == 1 || cmp(p2a*p2b) == 1) return false;
		res = l1.a + (p2a/(p2a-p2b)) * (l1.b - l1.a);
		return true;
	}
};
inline bool atRight(const point& a,const point& b) {
	return crossMul(a,b) > 0;
}

point p[32];
int cnt = 0;
inline bool angleCmp(const point& a,const point& b) {
	int res = crossMul(a-p[0],b-p[0]);
	if(res == 0)
		return (dist(a,p[0]) < dist(b,p[0]));
	else return res < 0;
}
 //p.size() >= 2 
void graham(stack<point>& S) {
	int pivot = 0;
	for(int i = 1; i < cnt; ++i) {
		if(p[i].y < p[pivot].y || (p[i].y == p[pivot].y && p[i].x < p[pivot].x)) {
			pivot = i;
		}
	}
	if(pivot != 0) swap(p[0],p[pivot]);
	sort(p+1,p+cnt,angleCmp);
	p[cnt++] = p[0];
	S.push(p[0]);
	S.push(p[1]);
	point x;
	for(int i = 2; i < cnt; ++i) {
		x = S.top(); S.pop();
		while(atRight(x-S.top(),p[i]-x)) {
			x = S.top();
			S.pop();
		}
		S.push(x);
		S.push(p[i]);
	}
	cnt--;
}
