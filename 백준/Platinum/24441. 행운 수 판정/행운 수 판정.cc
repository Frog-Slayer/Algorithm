#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

struct Segtree {
	int N;
	vector<int> tree;

	Segtree(int N) : N(N), tree(4 * N) {}

	void update(int node, int start, int end, int idx, int val) {
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] = val;
			return;
		}

		int mid = (start + end) / 2;

		if (idx <= mid) update(node * 2, start, mid, idx, val);
		else update(node * 2 + 1, mid + 1, end, idx, val);

		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	void update(int idx, int val) {
		update(1, 0, N - 1, idx, val);
	}

	int query(int node, int start, int end, int idx) {
		if (idx < start || end < idx) return 0;
		if (start == end) return tree[node]; 

		int mid = (start + end) / 2;

		return query(node * 2, start, mid, idx) + query(node * 2 + 1, mid + 1, end, idx);
	}
	
	int query(int idx) {
		return query(1, 0, N - 1, idx);
	}

	int bin_search(int node, int start, int end, int amt) {
		if (start == end) return start;

		int mid = (start + end) / 2;

		if (tree[node * 2] >= amt) return bin_search(node * 2, start, mid, amt);
		return bin_search(node * 2 + 1, mid + 1, end, amt - tree[node * 2]);
	}

	int bin_search(int amt) {
		return bin_search(1, 0, N - 1, amt);
	}
};

const int MAX_N = 1e6;

Segtree tree(MAX_N / 2 + 1);
vector<bool> lucky(MAX_N + 1);

void preprocess() {
	for (int i = 1; i <= MAX_N / 2; i++) tree.update(i, 1);

	for (int i = 2; tree.tree[1] >= i; i++) {
		int n = 2 * tree.bin_search(i) - 1;

		for (int j = tree.tree[1] / n * n; j > 0; j -= n) {
			int k = tree.bin_search(j);
			tree.update(k, 0);
		}
	}

	for (int i = 1; i <= MAX_N / 2; i++) lucky[2 * i - 1] = tree.query(i);
}

int main() {
	fastio;

	preprocess();

	int T;
	cin >> T;

	while (T--) {
		int n;
		cin >> n;

		cout << (lucky[n] ? "lucky\n" : "unlucky\n");
	}
}
