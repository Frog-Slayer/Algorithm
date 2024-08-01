#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAX_N = 1000000;
int N, M;

struct Node {
	int mx;
	int mx_count;
	int second_mx;
	ll sum;
};

Node tree[MAX_N * 4 + 4];

Node add(Node &lhs, Node& rhs) {
		Node ret;
		int mx = lhs.mx;
		int mx_count = lhs.mx_count;
		int second_mx = lhs.second_mx;
		ll sum = lhs.sum;

		if (lhs.mx == rhs.mx) {
			ret.mx = mx;
			ret.second_mx = max(second_mx, rhs.second_mx);
			ret.mx_count = mx_count + rhs.mx_count;
		}
		else if (mx > rhs.mx) {
			ret.mx = mx;
			ret.second_mx = max(second_mx, rhs.mx);
			ret.mx_count = mx_count;
		}
		else {
			ret.mx = rhs.mx;
			ret.second_mx = max(mx, rhs.second_mx);
			ret.mx_count = rhs.mx_count;
		}

		ret.sum = sum + rhs.sum;
		return ret;
	}
void propagate(int node, int start, int end) {
	if (start == end) return;

	for (int i = 0; i < 2; i++) {
		if (tree[node].mx < tree[node * 2 + i].mx) {
			tree[node * 2 + i].sum -= (ll)tree[node * 2 + i].mx_count * (tree[node * 2 + i].mx - tree[node].mx);
			tree[node * 2 + i].mx = tree[node].mx;
		}
	}
}

void init(int node, int start, int end, int idx, int val) {
	if (idx < start || end < idx) return;
	if (start == end) {
		tree[node] = { val, 1 , -1, val };
		return;
	}

	int mid = (start + end) / 2;
	init(node * 2, start, mid, idx, val);
	init(node * 2 + 1, mid + 1, end, idx, val);

	tree[node] = add(tree[node * 2], tree[node * 2 + 1]);

}

void update(int node, int start, int end, int left, int right, int val) {
	propagate(node, start, end);
	if (right < start || end < left || tree[node].mx <= val) return;
	if (left <= start && end <= right && tree[node].second_mx < val) {
		tree[node].sum -= (ll)tree[node].mx_count * (tree[node].mx - val);
		tree[node].mx = val;
		propagate(node, start, end);
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, left, right, val);
	update(node * 2 + 1, mid + 1, end, left, right, val);

	tree[node] = add(tree[node * 2], tree[node * 2 + 1]);
}

ll query_sum(int node, int start, int end, int left, int right) {
	propagate(node, start, end);
	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return tree[node].sum;

	int mid = (start + end) / 2;
	return query_sum(node * 2, start, mid, left, right) + query_sum(node * 2 + 1, mid + 1, end, left, right);
}

int query_max(int node, int start, int end, int left, int right) {
	propagate(node, start, end);
	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return tree[node].mx;

	int mid = (start + end) / 2;
	return max(query_max(node * 2, start, mid, left, right), query_max(node * 2 + 1, mid + 1, end, left, right));
}

int main() {
	scanf("%d", &N);

	for (int a, i = 1; i <= N; i++) {
		scanf("%d", &a);
		init(1, 1, N, i, a);
	}

	scanf("%d", &M);

	for (int i = 0; i < M; i++) {
		int t, l, r, x;
		scanf("%d%d%d", &t, &l, &r);

		if (t == 1) {
			scanf("%d", &x);
			update(1, 1, N, l, r, x);
		}
		else if (t == 2) printf("%d\n", query_max(1, 1, N, l, r));
		else printf("%lld\n", query_sum(1, 1, N, l, r));
	}
}