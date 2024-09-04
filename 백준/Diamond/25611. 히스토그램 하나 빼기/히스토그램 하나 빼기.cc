#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const int INF = 1e9 + 7;

struct Segtree {
	bool is_min = false;
	int N;
	vector<ll> tree, lazy;

	void resize(int _N){
		N = _N;
		tree.resize(4 * N, INF);
		lazy.resize(4 * N, INF);
	}

	void propagate(int node, int start, int end) {
		tree[node] = min(tree[node], lazy[node]);
		if (start != end) {
			lazy[node * 2] = min(lazy[node * 2], lazy[node]);
			lazy[node * 2 + 1] = min(lazy[node * 2 + 1], lazy[node]);
		}
		lazy[node] = INF;
	}

	void update(int node, int start, int end, int left, int right, ll val) {
		propagate(node, start, end);
		if (right < start || end < left) return;
		if (left <= start && end <= right) {
			lazy[node] = val;
			propagate(node, start, end);
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, val); 
		update(node * 2 + 1, mid + 1, end, left, right, val);
		tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	}

	void update(int left, int right, ll val) {
		update(1, 0, N - 1, left, right, val);
	}

	int leftmost(int node, int start, int end, int left, int right, int val) {
		propagate(node, start, end);
		if (right < start || end < left || tree[node] >= val) return left - 1;
		if (start == end) return start;

		int mid = (start + end) / 2;
		int lsub = leftmost(node * 2, start, mid, left, right, val);
		if (lsub != left - 1) return lsub;
		return leftmost(node * 2 + 1, mid + 1, end, left, right, val);
	}

	int rightmost(int node, int start, int end, int left, int right, int val) {
		propagate(node, start, end);
		if (right < start || end < left || tree[node] >= val) return right + 1;
		if (start == end) return start;
		int mid = (start + end) / 2;
		int rsub = rightmost(node * 2 + 1, mid + 1, end, left, right, val);
		if (rsub != right + 1) return rsub;
		return rightmost(node * 2, start, mid, left, right, val);
	}

	ll query(int node, int start, int end, int idx) {
		propagate(node, start, end);
		if (idx < start || end < idx) return INF;
		if (start == end) return tree[node];

		int mid = (start + end) / 2;
		return min(query(node * 2, start, mid, idx), query(node * 2 + 1, mid + 1, end, idx));
	}

	int leftmost(int left, int right, int val) {
		return leftmost(1, 0, N - 1, left, right, val);
	}
	
	int rightmost(int left, int right, int val) {
		return rightmost(1, 0, N - 1, left, right, val);
	}

	ll query(int idx) {
		return query(1, 0, N - 1, idx);
	}

} tree, ans;

int main() {
	int N;
	scanf("%d", &N);

	tree.resize(N + 2);
	ans.resize(N + 2);
	tree.update(0, 0, 0);
	tree.update(N + 1, N + 1, 0);

	vector<ll> h(N + 2);

	for (int i = 1; i <= N; i++) {
		scanf("%lld", &h[i]);
		tree.update(i, i, h[i]);
	}

	for (int i = 1; i <= N; i++) {
		int left = tree.rightmost(0, i - 1, h[i]);
		int right = tree.leftmost(i + 1, N + 1, h[i]);

		ans.update(left + 1, right - 1, -h[i] * (right - left - 2));
		ans.update(1, left, -h[i] * (right - left - 1));
		ans.update(right, N, -h[i] * (right - left -1));

		int left_left = tree.rightmost(0, left - 1, h[i]);
		ans.update(left, left, -h[i] * (right - left_left - 2)); 

		int right_right = tree.leftmost(right + 1, N + 1, h[i]);
		ans.update(right, right, -h[i] * (right_right- left - 2)); 
	}

	for (int i = 1; i <= N; i++) {
		printf("%lld ", -ans.query(i));
	}
}