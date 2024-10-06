#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()
#define fastio cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false)

const int INF = 1e5 + 3;

struct Segtree {
	struct Node {
		int mn = 0, mx = INF;
	};

	vector<Node> tree;

	Segtree() : tree(1 << 22) {}; 

	void f(int node, int mn, int mx) {
		tree[node].mn = min(max(tree[node].mn, mn), mx);
		tree[node].mx = min(max(tree[node].mx, mn), mx);
	}

	void propagate(int node, int start, int end) {
		if (start != end) {
			f(node * 2, tree[node].mn, tree[node].mx);
			f(node * 2 + 1, tree[node].mn, tree[node].mx);
			tree[node].mn = 0, tree[node].mx = INF;
		}

	}

	void update(int node, int start, int end, int left, int right, int mn, int mx) {
		propagate(node, start, end);
		if (right < start || end < left) return;
		if (left <= start && end <= right) {
			f(node, mn, mx);
			propagate(node, start, end);
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, mn, mx);
		update(node * 2 + 1, mid + 1, end, left, right, mn, mx);
	}

	int query(int node, int start, int end, int idx) {
		propagate(node, start, end);

		if (start == end) return tree[node].mn;

		int mid = (start + end) / 2;

		if (idx <= mid) return query(node * 2, start, mid, idx);
		return query(node * 2 + 1, mid + 1, end, idx); 
	}
} tree;

int main() {
	fastio;

	int N, K;
	cin >> N >> K;

	for (int i = 0; i < K; i++) {
		int op, left, right, height;
		cin >> op >> left >> right >> height;

		if (op == 1) tree.update(1, 0, N - 1, left, right, height, INF);
		else tree.update(1, 0, N - 1, left, right, 0, height);
	}

	for (int i = 0; i < N; i++) cout << tree.query(1, 0, N - 1, i) << '\n';
}