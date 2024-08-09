#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> v, order, ans;
vector<int> tree;

void update(int node, int start, int end, int idx, int val) {
	if (idx < start || end < idx) return;
	if (start == end) {
		tree[node] += val;
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, idx, val);
	update(node * 2 + 1, mid + 1, end, idx, val);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int query(int node, int start, int end, int val) {
	if (start == end) return start;

	int mid = (start + end) / 2;
	if (tree[node * 2] >= val) return query(node * 2, start, mid, val);
	return query(node * 2 + 1, mid + 1, end, val - tree[node * 2]);
}

int main() {
	scanf("%d", &N);

	tree.resize(4 * N);
	v.resize(N);
	order.resize(N);
	ans.resize(N);

	for (int i = 0; i < N; i++) scanf("%d", &v[i]);

	sort(v.begin(), v.end());

	for (int i = 0; i < N; i++) {
		int idx = lower_bound(v.begin(), v.end(), v[i]) - v.begin();
		update(1, 0, N - 1, idx, 1);
	}
	
	for (int i = 0; i < N; i++) scanf("%d", &order[i]);

	for (int i = N - 1; i >= 0; i--) {
		int q = query(1, 0, N - 1, order[i] + 1);
		ans[i] = v[q];
		update(1, 0, N - 1, q, -1);
	}

	for (int i = 0; i < N; i++) printf("%d\n", ans[i]);


}