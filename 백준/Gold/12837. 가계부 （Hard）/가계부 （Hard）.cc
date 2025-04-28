#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

struct Segtree {
	int N;
	vector<ll> tree;

	Segtree(int N): N(N), tree(4 * N) {}

	void update(int node, int start, int end, int idx, int val) {
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] += val;;
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, idx, val);
		update(node * 2 + 1, mid + 1, end, idx, val);

		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	void update(int idx, int val) {
		update(1, 0, N - 1, idx, val);
	}

	ll query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node];
	
		int mid = (start + end) / 2;
		return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
	}

	ll query(int left, int right) {
		return query(1, 0, N - 1, left, right);
	} };

int main() {
	fastio;

	int N, Q;
	cin >> N >> Q;
	Segtree tree(N + 1);

	for (int i = 0; i < Q; i++) {
		int t, p, q;
		cin >> t >> p >> q;

		if (t == 1) tree.update(p, q);
		else cout << tree.query(p, q) << '\n';
	}

	
}

