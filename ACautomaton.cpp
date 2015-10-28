const int maxn = 1000050;

int nCnt = 0;
struct Node {
	Node *child[26];
	Node *fail;
	int info;
} N[maxn];

inline Node *newNode() {
	memset(N[nCnt].child, 0,sizeof(N[nCnt].child));
	N[nCnt].fail = 0;
	N[nCnt].info = 0;
	return &N[nCnt++];
}

void insert(Node *root, char *str) {
	Node *iter = root;
	while(*str) {
		if(iter->child[*str-'a'] == 0) {
			iter->child[*str-'a'] = newNode();
		}
		iter = iter->child[*str-'a'];
		++str;
	}
	++iter->info;
}

void build(Node *root) {
	queue<Node*> Q;
	for(int i = 0; i < 26; ++i) {
		if(root->child[i]) {
			root->child[i]->fail = root;
			Q.push(root->child[i]);
		}
	}
	while(!Q.empty()) {
		Node *u = Q.front();
		Q.pop();
		for(int i = 0; i < 26; ++i) {
			if(u->child[i]) {
				Node *tmp = u->fail;
				while(tmp != root && tmp->child[i] == 0) {
					tmp = tmp->fail;
				}
				if(tmp->child[i]) {
					tmp = tmp->child[i];
				}
				u->child[i]->fail = tmp;
				Q.push(u->child[i]);
			}
		}
	}
}

int query(Node *root, char *str) {
	int ans = 0;
	Node *iter = root;
	while(*str) {
		while(iter != root && iter->child[*str-'a'] == 0) {
			iter = iter->fail;
		}
		if(iter->child[*str-'a']) {
			iter = iter->child[*str-'a'];
		}
		Node *tmp = iter;
		while(tmp != root && tmp->info != -1) {
			ans += tmp->info;
			tmp -> info = -1;
			tmp = tmp->fail;
		}
		++str;
	}
	return ans;
}
