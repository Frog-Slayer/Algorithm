#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;
int N;
vector<int> A, compressed;

struct Node {
	int len;
	int cnt;

	Node operator+(const Node& rhs) {
		if (len != rhs.len) return max(rhs); 
		return {len, (cnt + rhs.cnt) % MOD};
	}

	Node max(const Node& rhs) {
		if (len < rhs.len) return rhs;
		return *this;
	}
};

vector<Node> tree;

void update(int node, int start, int end, int left, int right, Node val) {
	if (right < start || end < left) return;
	if (start == end) {
		tree[node] = tree[node] + val;
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, left, right, val);
	update(node * 2 + 1, mid + 1, end, left, right, val);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void update(int idx, Node val) {
	update(1, 1, compressed.size(), idx, idx, val);
}

Node query(int node, int start, int end, int left, int right) {
	if (right < start || end < left) return {0, 0};
	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

Node query(int left, int right) {
	return query(1, 1, compressed.size(), left, right);
}

int main() {
	scanf("%d", &N);
	A.resize(N);

	for (int i = 0; i < N; i++) scanf("%d", &A[i]);

	compressed = vector<int>(A);
	sort(compressed.begin(), compressed.end());
	compressed.erase(unique(compressed.begin(), compressed.end()), compressed.end());

	tree.resize(compressed.size() * 4 + 4);

	for (int i = 0; i < N; i++) {
		A[i] = lower_bound(compressed.begin(), compressed.end(), A[i]) - compressed.begin() + 1;
		Node q = query(1, A[i] - 1);
		update(A[i], {q.len + 1, max(q.cnt, 1)});
	}

	printf("%d %d", tree[1].len, tree[1].cnt);

}