#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)); v.erase(unique(all(v)), v.end())

typedef long long ll;
const ll INF = 1e16;

struct Node {
	Node() {}
	Node(Node* node);

	ll val = 0;
	Node* left = NULL;
	Node* right = NULL;
};

Node::Node(Node* node) {
	this->val = node->val;
	this->left = node->left;
	this->right = node->right;
}

void update(Node *node, int start, int end, int idx) {
	node->val++;
	if (start == end) return;
	int mid = (start + end) / 2;

	if (idx <= mid) update(node->left = new Node(node->left), start, mid, idx);
	else update(node->right = new Node(node->right), mid + 1, end, idx);
}

int query(Node *node, int start, int end, int K) {
	if (start == end) return start;
	int cnt = node->left->val;
	int mid = (start + end) / 2;
	if (cnt >= K) return query(node->left, start, mid, K);
	return query(node->right, mid + 1, end, K - cnt);
}

void init(Node* node, int start, int end) {
	if (start == end) return;

	int mid = (start + end) / 2;
	init(node->left = new Node(), start, mid);
	init(node->right = new Node(), mid + 1, end);
}

int main() {
	int N, K;
	scanf("%d%d", &N, &K);

	vector<ll> A(N + 1), compressed;

	compressed.emplace_back(0);
	compressed.emplace_back(INF);

	for (int i = 1; i <= N; i++) {
		scanf("%lld", &A[i]);
		A[i] += A[i - 1];
		compressed.emplace_back(A[i]);
	}

	compress(compressed);
	for (int i = 0; i <= N; i++) A[i] = lower_bound(all(compressed), A[i]) - compressed.begin();

	vector<Node*> root(N + 1);

	root[0] = new Node();
	init(root[0], 0, compressed.size() - 1);
	update(root[0], 0, compressed.size() - 1, A[0]);

	priority_queue<tuple<ll, int, int>> pq;

	for (int i = 1; i <= N; i++) {
		int first = query(root[i - 1], 0, compressed.size() - 1, 1);
		update(root[i]= new Node(root[i - 1]), 0, compressed.size() - 1, A[i]);
		pq.push({compressed[A[i]] - compressed[first], i, 1});
	}

	priority_queue<ll> ans;

	while (!pq.empty() && ans.size() < K) {
		auto [sum, i, k] = pq.top();
		pq.pop();

		ans.push(sum);
		int next = query(root[i - 1], 0, compressed.size() - 1, k + 1);
		if (next == compressed.size() - 1) continue;
		pq.push({compressed[A[i]] - compressed[next], i, k + 1});
	}

	while (!ans.empty()) printf("%lld ", ans.top()), ans.pop();
}