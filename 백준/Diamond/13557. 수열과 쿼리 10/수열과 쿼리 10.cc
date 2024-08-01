#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll INF = 1e12;
int N, M;

struct Node {
	ll left;
	ll right;
	ll total;
	ll sum;

	Node operator+(const Node& rhs) {
		Node ret;

		ret.left = max(left, sum + rhs.left);
		ret.right = max(rhs.right, right + rhs.sum);
		ret.sum = sum + rhs.sum;

		ret.total = max({ret.left, ret.right, total, rhs.total, right + rhs.left});

		return ret;
	}
};

vector<Node> tree;

void update(int node, int start, int end, int idx, int val) {
	if (idx < start || end < idx) return;
	if (start == end) {
		tree[node] = { val, val, val, val};
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, idx, val);
	update(node * 2 + 1, mid + 1, end, idx, val);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

Node query(int node, int start, int end, int left, int right) {
	if (right < start || end < left) return { -INF, -INF, -INF, 0 };
	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

Node query(int left, int right) {
	return query(1, 1, N, left, right);
}

int main() {
	scanf("%d", &N);
	tree.resize(4 * N + 4);

	for (int a, i = 1; i <= N; i++) {
		scanf("%d", &a);
		update(1, 1, N, i, a);
	}

	scanf("%d", &M);

	for (int i = 0; i < M; i++) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

		ll ans;
		if (x2 <= y1) {//겹치는 경우
			Node left = query(x1, x2 - 1);
			Node mid = query(x2, y1);
			Node right = query(y1 + 1, y2);

			ans = max({mid.total, left.right + mid.left, right.left + mid.right, left.right + mid.sum + right.left});
		}
		else {//아닌 경우
			ans = query(1, 1, N, y1 + 1, x2 - 1).sum;

			ll left_right = query(1, 1, N, x1, y1).right;
			ans += left_right;

			ll right_left = query(1, 1, N, x2, y2).left;
			ans += right_left;
		}
		printf("%lld\n", ans);
	}
}