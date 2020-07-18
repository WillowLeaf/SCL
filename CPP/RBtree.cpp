enum RBcolor{RED = 0,BLACK = 1};
struct RBnode
{
	int key;
	bool color; //0 for red, 1 for black;
	RBnode *p;
	RBnode *left;
	RBnode *right;
	RBnode(int k = 0) : key(k),color(RED),p(0),left(0),right(0) {}
};
struct RBtree 
{
	RBnode *NIL;
	RBnode *root;
	RBtree() :NIL(new RBnode()) , root(NIL) {NIL->color = BLACK;}
	~RBtree() { while(root != NIL) remove(root); delete NIL; }
	void leftRotate(RBnode *z);
	void rightRotate(RBnode *z);
	void insert(int key);
	void insert_fix(RBnode *z);
	void remove(RBnode *iter);
	void remove_fix(RBnode *x);
	void print(RBnode *node,int indent);
	RBnode *find(int key);
	RBnode *findMin(RBnode *T);
	RBnode *findSuccessor(RBnode *node);
};


RBnode *RBtree::findMin(RBnode *T)
{
	while(T->left != NIL)
		T = T->left;
	return T;
}

RBnode *RBtree::find(int key)
{
	RBnode *iter = root;
	while(iter != NIL && iter->key != key) {
		if(key > iter->key)
			iter = iter->right;
		else
			iter = iter->left;
	}
	return iter;
}
RBnode *RBtree::findSuccessor(RBnode *node) 
{
	if(node->right != NIL) 
		return findMin(node->right);
	RBnode *iter = node;
	while(iter->p != NIL && iter != iter->p->left) {
		iter = iter->p;
	}
	return iter->p;
}

void RBtree::remove_fix(RBnode *x)
{
	while(x->color == BLACK && x != root) {
		RBnode *w;
		if(x == x->p->left) {
			w = x->p->right;
			if(w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				leftRotate(x->p);
				w = x->p->right;
			}
			if(w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			} else {
				if(w->right->color == BLACK) {
					w->color = RED;
					w->left->color = BLACK;
					rightRotate(w);
					w = x->p->right;
				}
				w->right->color = BLACK;
				w->color = x->p->color;
				x->p->color = BLACK;
				leftRotate(x->p);
				x = root;
			}
		} else {
			w = x->p->left;
			if(w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				rightRotate(x->p);
				w = x->p->left;
			}
			if(w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->p;
			} else {
				if(w->left->color == BLACK) {
					w->color = RED;
					w->right->color = BLACK;
					leftRotate(w);
					w = x->p->left;
				}
				w->left->color = BLACK;
				w->color = x->p->color;
				x->p->color = BLACK;
				rightRotate(x->p);
				x = root;
			}
		}
	}
	x->color = BLACK;
	return;
}
void RBtree::remove(RBnode *iter)
{
	RBnode *y;
	if(iter->left == NIL || iter->right == NIL) {
		y = iter;
	} else { y = findSuccessor(iter); }
	RBnode *x;
	if(y->left == NIL) {
		x = y->right;
	} else { x = y->left; }
	x->p = y->p;
	if(y->p == NIL) {
		root = x;
	} else if(y == y->p->left) {
		y->p->left = x;
	} else {
		y->p->right = x;
	}
	if(y != iter) {
		iter->key = y->key;
	}
	if(y->color == BLACK)
		remove_fix(x);
	delete y;
}


void RBtree::print(RBnode *node,int indent)
{
	for(int i = 0; i < indent; ++i)
		putchar('-');
	printf("%d(%d)",node->key,node->color);
	putchar('\n');
	if(node->left != NIL) {
		print(node->left,indent + 4);
	}
	if(node->right != NIL) {
		print(node->right,indent + 4);
	}
}

void RBtree::leftRotate(RBnode *z)
{
	RBnode *y = z->right;
	y->p = z->p;
	if(z->p == NIL) {
		root = y;
	} else if(z == z->p->left) {
		z->p->left = y;
	} else {
		z->p->right = y;
	}
	y->left->p = z;
	z->right = y->left;
	z->p = y;
	y->left = z;
}
void RBtree::rightRotate(RBnode *z)
{
	RBnode *y = z->left;
	y->p = z->p;
	if(z->p == NIL) {
		root = y;
	} else if(z == z->p->right) {
		z->p->right = y;
	} else {
		z->p->left = y;
	}
	y->right->p = z;
	z->left = y->right;
	z->p = y;
	y->right = z;
}
void RBtree::insert_fix(RBnode *z)
{
	while(z->p->color == RED) {
		if(z->p->p->left == z->p) {
			RBnode *y = z->p->p->right;
			if(y->color == RED) {
				z->p->color = y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			} else {
				if(z == z->p->right) {
					z = z->p;
					leftRotate(z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				rightRotate(z->p->p);
			}
		} else {
			RBnode *y = z->p->p->left;
			if(y->color == RED) {
				z->p->color = y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			} else {
				if(z == z->p->left) {
					z = z->p;
					rightRotate(z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				leftRotate(z->p->p);
			}
		}
	}
	root->color = BLACK;
}
void RBtree::insert(int key)
{
	RBnode *y = NIL, *x = root;
	while(x != NIL) {
		y = x;
		if(key < x->key) 
			x = x->left;
		else x = x->right;
	}
	RBnode *z = new RBnode(key);
	z->left = z->right = NIL;
	z->p = y;
	if(y == NIL) {
		root = z;
	} else if(key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}
	insert_fix(z);
}
