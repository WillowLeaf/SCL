struct Node {
	Node *ch[2];
	Node *p;

	int val;

	int size;
	int sum;
	int lmx;
	int rmx;
	int mx;

	bool lzSame;
	bool lzRev;

	void relax();
	void update() {
		size = 1 + ch[0]->size + ch[1]->size;
		sum = val + ch[0]->sum + ch[1]->sum;
		lmx = max(ch[0]->lmx, max(ch[0]->sum + val, ch[0]->sum + val + ch[1]->lmx));
		rmx = max(ch[1]->rmx, max(ch[1]->sum + val, ch[1]->sum + val + ch[0]->rmx));
		mx = max(max(ch[0]->mx, ch[1]->mx), max(0, ch[0]->rmx) + val + max(0, ch[1]->lmx));
	}
	int dir() {
		return this == p->ch[1];
	}
	void setch(Node *node, int d) {
		ch[d] = node;
		node->p = this;
	}
};
const int inf = 0x3f3f3f3f;

struct Splay {
	static Node *NIL;
	Node *root;
	
	Splay() {
		NIL->p = NIL->ch[0] = NIL->ch[1] = NIL;
		NIL->mx = NIL->lmx = NIL->rmx = -inf;
		root = makeNode();
		root->setch(makeNode(), 0);
		root->ch[0]->update();
		root->update();
	}
	void rotate(Node *x) {
		Node *y = x->p;
		y->relax();
		y->ch[0]->relax();
		y->ch[1]->relax();
		x->ch[0]->relax();
		x->ch[1]->relax();
		int d = x->dir();
		y->p->setch(x, y->dir());
		y->setch(x->ch[!d], d);
		x->setch(y, !d);
		y->update();
		x->update();
		if(root == y) 
			root = x;
	}
	
	void splay(Node *x, Node *f) {
		while(x->p != f) {
			Node *y = x->p;
			if(y->p == f) {
				rotate(x);
			} else if(x->dir() == y->dir()) {
				rotate(y);
				rotate(x);
			} else {
				rotate(x);
				rotate(x);
			}
		}
	}

	void select(int k, Node *f) {
		Node *iter = root;
		while(true) {
			iter->relax();
			int sz = iter->ch[0]->size;
			if(k < sz + 1) {
				iter = iter->ch[0];
			} else if(k == sz + 1) {
				break;
			} else {
				k -= sz + 1;
				iter = iter->ch[1];
			}
		}

		splay(iter, f);
	}

	Node *makeNode() {
		Node *node = new Node();
		node->p = node->ch[0] = node->ch[1] = NIL;
		return node;
	}
	Node *build(int l, int r) {
		if(l > r) return NIL;
		int m = (l + r) >> 1;
		Node *node = makeNode();
		node->setch(build(l, m-1), 0);
		scanf("%d", &node->val);
		node->setch(build(m+1, r), 1);
		node->update();
		return node;
	}
	void insert(int pos, int tot) {
		select(pos + 1, NIL);
		select(pos + 2, root);
		root->ch[1]->setch(build(1, tot), 0);
		splay(root->ch[1]->ch[0], NIL);
	}

	void destroy(Node *x) {
		if(x != NIL) {
			destroy(x->ch[0]);
			destroy(x->ch[1]);
			delete x;
		}
	}
	void remove(int pos, int tot) {
		select(pos, NIL);
		select(pos+1+tot, root);
		destroy(root->ch[1]->ch[0]);
		root->ch[1]->setch(NIL, 0);
		splay(root->ch[1], NIL);
	}
	void reverse(int pos, int tot) {
		select(pos, NIL);
		select(pos+1+tot, root);
		root->ch[1]->ch[0]->lzRev ^= 1;
		splay(root->ch[1]->ch[0], NIL);
	}
	void makeSame(int pos, int tot, int val) {
		select(pos, NIL);
		select(pos+1+tot, root);
		root->ch[1]->ch[0]->val = val;
		root->ch[1]->ch[0]->lzSame = true;
		splay(root->ch[1]->ch[0], NIL);
	}
	int getSum(int pos, int tot) {
		select(pos, NIL);
		select(pos+1+tot, root);
		return root->ch[1]->ch[0]->sum;
	}
	int maxSum() {
		select(1, NIL);
		select(root->size, root);
		return root->ch[1]->ch[0]->mx;
	}
};


void Node::relax() {
	if(this == Splay::NIL) return ;
	if(lzSame) {
		ch[0]->val = ch[1]->val = val;
		ch[0]->lzSame = ch[1]->lzSame = true;
		sum = val * size;
		lmx = rmx = mx = (val > 0 ? sum : val);
		lzSame = false;
	}
	if(lzRev) {
		swap(ch[0], ch[1]);
		ch[0]->lzRev ^= 1;
		ch[1]->lzRev ^= 1;
		swap(lmx, rmx);
		lzRev = false;
	}
}

Node *Splay::NIL = new Node();

