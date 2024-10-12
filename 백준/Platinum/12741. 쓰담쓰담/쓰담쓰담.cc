#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

typedef long long ll;
const int INF = 1e9 + 7;

struct Segtree{
	int N;
	vector<bool> tree;

	Segtree() {}
	Segtree(int _N) : tree(4 * _N + 4), N(_N) {}

	void update(int node, int start, int end, int idx, bool val) {
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] = val;
			return;
		}

		int mid = (start + end) / 2;
		if (idx <= mid) update(node * 2, start, mid, idx, val);
		else update(node * 2 + 1, mid + 1, end, idx, val);

		tree[node] = tree[node * 2] || tree[node * 2 + 1];
	}

	void update(int idx, int val) {
		update(1, 1, N, idx, val);
	}

	bool query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return false;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return query(node * 2, start, mid, left, right) || query(node * 2 + 1, mid + 1, end, left, right);
	}

	bool query(int left, int right){
		return query(1, 1, N, left, right);
	}
};

int main() {
	fastio;

	int N, XY;
	cin >> N >> XY;

	vector<ll> A(N + 2);
	A[N + 1] = INF;

	Segtree tree(N + 1);

	for (int i = 1; i <= N; i++) {
		cin >> A[i];
		tree.update(i, A[i] < A[i - 1]);
	}

	for (int i = 0; i < XY; i++) {

		int Q, L, R;
		cin >> Q >> L >> R;

		if (Q == 1) {
			if (L < R && tree.query(L + 1, R)) cout << "HSS090\n";
			else cout << "CS204\n";
		}
		else {
			swap(A[L], A[R]);
			tree.update(L, A[L] < A[L - 1]);
			tree.update(L + 1, A[L + 1] < A[L]);
			tree.update(R, A[R] < A[R - 1]);
			tree.update(R + 1, A[R + 1] < A[R]);
		}
	}
}
