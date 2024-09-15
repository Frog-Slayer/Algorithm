#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()

const int MAX_N = 1e6 + 1;
int N, Q;

struct Node {
	int val;
	int left;
	int right;

	Node () {}
	Node (int _val, int _left, int _right) : val(_val), left(_left), right(_right) {}
};

int cnt = 0;
vector<int> root(MAX_N);
vector<Node> nodes(MAX_N * 21 * 2);

void update(int node, int start, int end, int idx, int val) {
	nodes[node].val += val;

	if (start == end) return; 

	int mid = (start + end) / 2;
	if (idx <= mid) {
		int left = nodes[node].left;
		int right = nodes[node].right;
		nodes[++cnt] = nodes[left];
		nodes[node].left = left = cnt;
		update(left, start, mid, idx, val);
		return;
	}

	int left = nodes[node].left;
	int right = nodes[node].right;
	nodes[++cnt] = nodes[right];
	nodes[node].right =  right = cnt;
	update(right, mid + 1, end, idx, val);
	return;
}

int query(int node, int start, int end, int left, int right) {
	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return nodes[node].val;
	
	int mid = (start + end) / 2;
	return query(nodes[node].left, start, mid, left, right) + query(nodes[node].right, mid + 1, end, left, right);
}

vector<int> arr(MAX_N);
vector<int> compressed, prv(MAX_N);

int main() {
	scanf("%d", &N);

	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
		compressed.emplace_back(arr[i]);
	}

	sort(all(compressed));
	compressed.erase(unique(all(compressed)), compressed.end());

	for (int i = 1; i <= N; i++) arr[i] = lower_bound(all(compressed), arr[i]) - compressed.begin();
	vector<int> tmp(compressed.size(), 0);

	for (int i = 1; i <= N; i++) {
		prv[i] = tmp[arr[i]];
		tmp[arr[i]] = i;
	}

	root[0] = ++cnt;

	for (int i = 1; i <= N; i++) {
		root[i] = ++cnt;
		nodes[root[i]] = nodes[root[i - 1]];
		update(root[i], 1, N, i, 1);
		if (prv[i]) {
			nodes[++cnt] = nodes[root[i]];
			root[i] = cnt;
			update(root[i], 1, N, prv[i], -1);
		}
	}

	scanf("%d", &Q);

	int q = 0;
	for (int i = 0; i < Q; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", q = query(root[r], 1, N, l, r));
	}
}