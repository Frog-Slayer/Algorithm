#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

struct Segtree {
	vector<int> tree;

	Segtree(int N) : tree(4 * N) {}

	void update(int node, int start, int end, int idx, int val) {
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] = val;
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, idx, val);
		update(node * 2 + 1, mid + 1, end, idx, val);

		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	int query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
	}
};

int main() {
	fastio;

	int N;
	cin >> N;

	Segtree tree(N);

	for (int i = 1; i <= N; i++) {
		int a;
		cin >> a;

		tree.update(1, 1, N, i, a & 1);
	}

	int M;
	cin >> M;

	for (int i = 0; i < M; i++) {
		int op, l, r;
		cin >> op >> l >> r;

		if (op == 1) tree.update(1, 1, N, l, r & 1);
		else if (op == 2) cout << (r - l + 1) - tree.query(1, 1, N, l, r) << '\n';
		else cout << tree.query(1, 1, N, l ,r) << '\n';
	}
}

