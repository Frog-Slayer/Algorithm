#include <iostream>
using namespace std;

const int MAX_HEIGHT = 3e6 + 4;
const int MAX_N = 3e5;
int N, M;
int height[MAX_N];

struct Segtree{
	int tree[MAX_HEIGHT * 4 + 4];
	int lazy[MAX_HEIGHT * 4 + 4];

	void propagate(int node, int start, int end) {
		if (lazy[node]) {
			tree[node] += (end - start + 1) * lazy[node];

			if (start != end) {
				lazy[node * 2] += lazy[node];
				lazy[node * 2 + 1] += lazy[node];
			}

			lazy[node] = 0;
		}
	}

	void update(int node, int start, int end, int left, int right, int val) {
		propagate(node, start, end);
		if (right < start || end < left) return;
		if (left <= start && end <= right) {
			lazy[node] += val;
			propagate(node, start, end);
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, val);
		update(node * 2 + 1, mid + 1, end, left, right, val);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	int query(int node, int start, int end, int left, int right) {
		propagate(node, start, end);
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
	}

	int get_acc_index(int node, int start, int end, int val){
		propagate(node, start, end);

		if (start == end) return start;

		int mid = (start + end) / 2;

		propagate(node * 2, start, mid);
		propagate(node * 2 + 1, mid + 1, end);
		if (tree[node * 2] >= val) return get_acc_index(node * 2, start, mid, val);
		return get_acc_index(node * 2 + 1, mid + 1, end, val - tree[node * 2]);
	}

} score_tree, height_tree;


void input_score(int can) {
	for (int i = 0; i < N; i++) {//black
		int n;
		scanf("%d", &n);
		score_tree.update(1, 1, MAX_HEIGHT, height[i] + 1, height[i] + n, can);
		height[i] += n;
	}
}

int main() {
	scanf("%d", &N);

	input_score(1);
	input_score(2);
	input_score(5);

	scanf("%d", &M);

	height_tree.update(1, 1, MAX_HEIGHT, 1, MAX_HEIGHT, 1);

	for (int i = 0; i < M; i++) {
		int n;
		scanf("%d", &n);

		n = height_tree.get_acc_index(1, 1, MAX_HEIGHT, n); 
		printf("%d\n", score_tree.query(1, 1, MAX_HEIGHT, n, n));

		height_tree.update(1, 1, MAX_HEIGHT, n, n, -1);
	}
}