#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const int MAX_A = 1000000;
const int MAX_N = 100000;
int N, Q;
int divisor_cnt[MAX_A + 1];
vector<int> A;

struct Segtree {
	vector<pair<ll, bool>> tree;

	Segtree() {
		tree.resize(4 * MAX_N + 4);
	}

	void update(int node, int start, int end, int left, int right, int val) {
		if (right < start || end < left || (!val && !tree[node].second)) return;
		if (start == end) {
			if (val) tree[node].first = val;
			else tree[node].first = divisor_cnt[tree[node].first];

			tree[node].second = tree[node].first > 2;
			return;
		}

		int mid = (start + end) / 2;

		update(node * 2, start, mid, left, right, val);
		update(node * 2 + 1, mid + 1, end, left, right, val);

		tree[node].first = tree[node * 2].first + tree[node * 2 + 1].first;
		tree[node].second = tree[node * 2].second || tree[node * 2 + 1].second;
	}

	void update(int left, int right, int val) {
		update(1, 1, N, left, right, val);
	}

	ll query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node].first;

		int mid = (start + end) / 2;
		return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
	}

	ll query(int left, int right) {
		return query(1, 1, N, left, right);
	}

} segtree;

void preprocess(){
	for (int i = 1; i <= MAX_A; i++) {
		for (int j = 1; i * j <= MAX_A; j++) {
			divisor_cnt[i * j]++;
		}
	}
}

int main() {
	scanf("%d%d", &N, &Q);
	A.resize(N + 1);
	
	preprocess();

	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
		segtree.update(i, i, A[i]);
	}

	for (int i = 0; i < Q; i++) {
		int t, s, e;
		scanf("%d%d%d", &t, &s, &e);
		if (t == 1) segtree.update(s, e, 0);
		else printf("%lld\n", segtree.query(s, e));
	}
}