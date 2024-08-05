#include <iostream>
#include <vector>
using namespace std;

int N, M;
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
	tree.resize(4 * N + 4);

	for (int s, i = 1; i <= N; i++) {
		scanf("%d", &s);
		update(1, 1, N, i, s);
	}

	scanf("%d", &M);

	for (int i = 0; i < M; i++) { 
		int cmd;
		scanf("%d", &cmd);

		if (cmd == 1) {
			int idx, amt;
			scanf("%d%d", &idx, &amt);
			update(1, 1, N, idx, amt);
		}
		else {
			int idx;
			scanf("%d", &idx);
			printf("%d\n", query(1, 1, N, idx));
		}

	}
}