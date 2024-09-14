#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()

const int MAX_N = 100000;
int N, M;
int sparse_table[18][MAX_N + 1], depth[MAX_N + 1];
vector<int> weight, compressed;
vector<vector<int>> adj;

int find_lca(int u, int v) {
	if (depth[u] > depth[v]) swap(u, v);
	int diff = depth[v] - depth[u];
	int i = 0;

	while (diff) {
		if (diff & 1) v = sparse_table[i][v];
		diff >>= 1;
		i++;
	}

	if (u == v) return u;

	for (int i = 17; i >= 0; i--) {
		if (sparse_table[i][u] != sparse_table[i][v]) {
			u = sparse_table[i][u];
			v = sparse_table[i][v];
		}
	}

	return sparse_table[0][u];
}

struct Node {
	int val = 0;
	Node *left = NULL;
	Node *right = NULL;

	Node () {}
	Node (int _val, Node* _left, Node *_right) : left(_left), right(_right), val(_val) {}
	Node* update(int start, int end, int idx);
} ;

vector<Node*> root(MAX_N + 1);

Node *Node::update(int start, int end, int idx) {
	if (idx < start || end < idx) return this;
	if (start == end) return new Node(val + 1, root[0], root[0]);

	int mid = (start + end) / 2;
	return new Node(val + 1, this->left->update(start, mid, idx), this->right->update(mid + 1, end, idx));
}

int query(Node *u, Node *v, Node *lca, Node *lca_parent, int left, int right, int K) {
	if (left == right) return left;

	int cnt = u->left->val + v->left->val - lca->left->val - lca_parent->left->val;

	int mid = (left + right) / 2;
	if (cnt >= K) return query(u->left, v->left, lca->left, lca_parent->left, left, mid, K);
	return query(u->right, v->right, lca->right, lca_parent->right, mid + 1, right, K - cnt);
}

void make_tree(int parent, int cur, int d) {
	depth[cur] = d;
	root[cur] = root[parent]->update(0, compressed.size() - 1, weight[cur]);

	for (auto &child : adj[cur]) {
		if (child != parent) {
			sparse_table[0][child] = cur;
			make_tree(cur, child, d + 1);
		}
	}
}

int main() {
	scanf("%d%d", &N, &M);
	weight.resize(N + 1);
	adj.resize(N + 1);

	for (int i = 1; i <= N; i++) {
		scanf("%d", &weight[i]);
		compressed.emplace_back(weight[i]);
	}

	sort(all(compressed));
	compressed.erase(unique(all(compressed)), compressed.end());

	for (int i = 1; i <= N; i++) weight[i] = lower_bound(all(compressed), weight[i]) - compressed.begin();

	for (int i = 0; i < N - 1; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		adj[x].emplace_back(y);
		adj[y].emplace_back(x);
	}

	root[0] = new Node();
	root[0]->left = root[0]->right = root[0];

	make_tree(0, 1, 0);

	for (int i = 1; i < 18; i++) {
		for (int j = 1; j <= N; j++) {
			sparse_table[i][j] = sparse_table[i - 1][sparse_table[i - 1][j]];
		}
	}

	for (int i = 0; i < M; i++) {//query
		int x, y, k;
		scanf("%d%d%d", &x, &y, &k);

		int lca = find_lca(x, y);
		int lca_parent = sparse_table[0][lca];

		int q = query( root[x], root[y], root[lca], root[lca_parent], 0, compressed.size() - 1, k); 
		printf("%d\n", compressed[q]); 
	}
}