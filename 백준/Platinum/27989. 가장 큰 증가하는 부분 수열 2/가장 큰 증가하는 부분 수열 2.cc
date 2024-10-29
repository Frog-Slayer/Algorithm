#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

struct Segtree {
	int N;
	vector<ll> tree;

	Segtree(int _N) : N(_N), tree(4 * _N, 0) {}

	void update(int node, int start, int end, int idx, ll val) {
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] = max(tree[node], val);
			return;
		}
	
		int mid = (start + end) / 2;
		update(node * 2, start, mid, idx, val);
		update(node * 2 + 1, mid + 1, end, idx, val);

		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}

	void update(int idx, ll val) {
		update(1, 0, N - 1, idx, val);
	}

	ll query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return max(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
	
	}

	ll query(int left, int right) {
		return query(1, 0, N - 1, left, right);
	}
};

int main() {
	fastio;

	int N;
	cin >> N;
	
	vector<ll> A(N), compressed(N);

	for (int i = 0; i < N; i++) {
		cin >> A[i];
		compressed[i] = A[i];
	}

	sort(all(compressed));
	compressed.erase(unique(all(compressed)), compressed.end());

	Segtree tree(compressed.size());

	for (int i = 0; i < N; i++) {
		int idx = lower_bound(all(compressed), A[i]) - compressed.begin();

		ll query = tree.query(0, idx - 1);
		tree.update(idx, query + A[i]);
	}

	cout << tree.tree[1];
}