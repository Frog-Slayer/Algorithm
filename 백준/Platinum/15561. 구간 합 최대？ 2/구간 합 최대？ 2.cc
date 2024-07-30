#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int INF = 1e9;
int N, Q, U, V;

struct Node {
	int left;
	int right;
	int sum;
	int total;

	Node() : left(-INF), right(-INF), sum(0), total(-INF) {}
	Node(int val) : left(val), right(val), sum(val), total(val) {}
};

vector<Node> tree;

void update(int node, int start, int end, int idx, int val) {
	if (idx < start || end < idx) return;
	if (start == end) {
		tree[node] = Node(val); 
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, idx, val);
	update(node * 2 + 1, mid + 1, end, idx, val);

	Node &ret = tree[node];
	Node &lsub = tree[node * 2], &rsub = tree[node * 2 + 1];

	ret.left = max(lsub.left, lsub.sum + rsub.left);
	ret.right = max(rsub.right, rsub.sum + lsub.right);
	ret.sum = lsub.sum + rsub.sum;
	ret.total = max({ret.left, ret.right, lsub.right + rsub.left, lsub.total, rsub.total});
}

void update(int idx, int val) {
	update(1, 1, N, idx, val);
}

Node query(int node, int start, int end, int left, int right) {
	if (right < start || end < left) return Node();
	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	Node lsub = query(node * 2, start, mid, left, right), rsub = query(node * 2 + 1, mid + 1, end, left, right);

	Node ret;
	ret.left = max(lsub.left, lsub.sum + rsub.left);
	ret.right = max(rsub.right, rsub.sum + lsub.right);
	ret.sum = lsub.sum + rsub.sum;
	ret.total = max({ret.left, ret.right, lsub.right + rsub.left, lsub.total, rsub.total});
	
	return ret;
}

int query(int left, int right) {
	Node q = query(1, 1, N, left, right);
	return q.total;
}

int main() {
	scanf("%d%d%d%d", &N, &Q, &U, &V);
	tree.resize(4 * N + 4);

	for (int i = 1; i <= N; i++) {
		int k;
		scanf("%d", &k);
		update(i, U * k + V);
	}

	for (int i = 0; i < Q; i++) {
		int c, a, b;
		scanf("%d%d%d", &c, &a, &b);

		if (!c) {
			int q = query(a, b) - V;
			printf("%d\n", q);
		}
		else update(a, U * b + V);
	}
}