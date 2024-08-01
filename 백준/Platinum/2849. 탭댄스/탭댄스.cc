#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, Q;

struct Node {
	int left = 0, right = 0, total = 0;
	int start = 0, end = 0;
};

vector<Node> tree;

void update(int node, int start, int end, int idx) {
	if (idx < start || end < idx) return;
	if (start == end) {
		tree[node].start = tree[node].end = 1 - tree[node].start;

		tree[node].left = tree[node].right = tree[node].total = 1;
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, idx);
	update(node * 2 + 1, mid + 1, end, idx);

	Node &left_sub = tree[node * 2];
	Node &right_sub = tree[node * 2 + 1];
	Node &ret = tree[node];

	ret.start = left_sub.start;
	ret.end = right_sub.end;

	ret.left = left_sub.left;
	ret.right = right_sub.right;

	ret.total = max(left_sub.total, right_sub.total);

	if (left_sub.end != right_sub.start) {
		if (left_sub.total == (mid - start + 1)) ret.left = left_sub.total + right_sub.left;
		if (right_sub.total == (end - mid)) ret.right = right_sub.total + left_sub.right;
		ret.total = max({ret.total, left_sub.right + right_sub.left, ret.left, ret.right});
	}
}

int main(){
	scanf("%d%d", &N, &Q);
	tree.resize(4 * (N + 1));

	for (int i = 1; i <= N; i++) update(1, 1, N, i);

	for (int i = 0; i < Q; i++) {
		int q;
		scanf("%d", &q);
		update(1, 1, N, q);

		printf("%d\n",  tree[1].total);
	}
}