#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

struct Segtree{
	vector<int> tree;

	Segtree(int N): tree(4 * N) {
		init(1, 0, N - 1);
	}

	void init(int node, int start, int end) {
		if (start == end) {
			tree[node] = 1;
			return;
		}

		int mid = (start + end) / 2;
		init(node * 2, start, mid);
		init(node * 2 + 1, mid + 1, end);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	void update(int node, int start, int end, int idx) {
		if (idx < start || end < idx) return;
		tree[node]--;
		if (start == end) return;

		int mid = (start + end) / 2;
		if (idx <= mid) update(node * 2, start, mid, idx);
		else update(node * 2 + 1, mid + 1, end, idx);
	}

	int query(int node, int start, int end, int val) {
		if (start == end) return start;
		int mid = (start + end) / 2;

		if (val < tree[node * 2 + 1]) return query(node * 2 + 1, mid + 1, end, val);
		return query(node * 2, start, mid, val - tree[node * 2 + 1]);
	}
};

int main() {
	fastio;
	int N;
	cin >> N;

	vector<int> inv(N), origin(N);
	Segtree tree(N);

	for (int i = 0; i < N; i++) cin >> inv[i];

	for (int i = N - 1; i >= 0; i--) {
		int q = tree.query(1, 0, N - 1, inv[i]);
		origin[q] = i + 1;
		tree.update(1, 0, N - 1, q);
	}
    
	for (int &n : origin) cout << n << ' ';
}

