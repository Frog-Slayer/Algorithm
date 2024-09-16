#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()

typedef long long ll;
const int MAX_N = 1 << 19;
int N, Q;

struct Node {
	int val = 0;
	int left = 0;
	int right = 0;

	Node () {}
	Node (int _val, int _left, int _right) : val(_val), left(_left), right(_right) {}
};

vector<int> root(MAX_N);
vector<Node> tree(MAX_N * 19);
int node_idx;

void update(int node, int start, int end, int idx, int val) {
	tree[node].val += val;
	if (start == end) return;

	int mid = (start + end) / 2;

	int left = tree[node].left, right = tree[node].right;

	if (idx <= mid) {//left
		tree[++node_idx] = tree[left];
		tree[node].left = left = node_idx;
		update(left, start, mid, idx, val);
		return;
	}
	//right
	tree[++node_idx] = tree[right];
	tree[node].right = right = node_idx;
	update(right, mid + 1, end, idx, val);
}

int leq_query(int start, int end, int left, int right, int x) {
	if (start == end) return tree[right].val - tree[left].val;
	int mid = (start + end) / 2;

	if (x <= mid) return leq_query(start, mid, tree[left].left, tree[right].left, x); 
	int sum = tree[tree[right].left].val - tree[tree[left].left].val;
	return sum + leq_query(mid + 1, end, tree[left].right, tree[right].right, x);
}

int xor_query(int level, int start, int end, int left, int right, int x) {
	if (start == end) return start;
	int mid = (start + end) / 2;
	if ((1 << (level -1)) & x) {
		int left_sum = tree[tree[right].left].val - tree[tree[left].left].val;
		if (left_sum) return xor_query(level - 1, start, mid, tree[left].left, tree[right].left, x);
		return xor_query(level - 1, mid + 1, end, tree[left].right, tree[right].right, x);
	}

	int right_sum = tree[tree[right].right].val - tree[tree[left].right].val;
	if (right_sum) return xor_query(level - 1, mid + 1, end, tree[left].right, tree[right].right, x);
	return xor_query(level - 1, start, mid, tree[left].left, tree[right].left, x);
}

int kth_min_query(int start, int end, int left, int right, int k) {
	if (start == end) return start;
	int mid = (start + end) / 2;
	int left_sum = tree[tree[right].left].val - tree[tree[left].left].val;

	if (left_sum >= k) return kth_min_query(start, mid, tree[left].left, tree[right].left , k);
	return kth_min_query(mid + 1, end, tree[left].right, tree[right].right, k - left_sum);
}

int main() {
	int M;
	scanf("%d", &M);

	root[0] = ++node_idx;

	for (int cur = 1, i = 1; i <= M; i++) {
		int t;
		scanf("%d", &t);

		int l, r, x;
		if (t == 1 || t == 3) scanf("%d", &x);
		else scanf("%d%d%d", &l, &r, &x);

		switch (t) {
			case 1://update
				root[cur] = ++node_idx;
				tree[node_idx] = tree[root[cur - 1]];
				update(root[cur], 0, MAX_N - 1, x, 1);
				cur++;
				break;
			case 2://xor
				printf("%d\n", xor_query(19, 0, MAX_N - 1, root[l - 1], root[r], x));
				break;
			case 3://erase k
				cur -= x;
				break;
			case 4://leq
				printf("%d\n", leq_query(0, MAX_N - 1, root[l - 1], root[r], x));
				break;
			case 5://kth
				printf("%d\n", kth_min_query(0, MAX_N - 1, root[l - 1], root[r], x));
		}
	}
}