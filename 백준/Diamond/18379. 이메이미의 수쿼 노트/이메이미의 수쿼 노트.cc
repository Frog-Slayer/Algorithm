#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;
#define fastio cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false)

typedef long long ll;
const int MOD = 998'244'353;

struct Node {
	Node() {}
	Node(int i); 
	int left = 0;
	int right = 0;

	int val = 0;
	int mult = 1;
	int add = 0;
};

vector<Node> nodes;

Node::Node(int i) {
	Node &node = nodes[i];
	val = node.val;
	mult = node.mult;
	add = node.add;
	left = node.left;
	right = node.right;
}

int add_node(int i = 0) {
	nodes.emplace_back(Node(i));
	return nodes.size() - 1; 
}

void propagate(int root, int start, int end) {
	Node &node = nodes[root];
	if (node.mult == 1 && node.add == 0) return;
	node.val = ((ll)node. mult * node.val + (ll)(end - start + 1) * node.add) % MOD;

	if (start != end) {
		int lidx = node.left = add_node(node.left);
		int ridx = node.right = add_node(node.right);

		Node &left = nodes[lidx];
		Node &right = nodes[ridx];

		left.mult = ((ll)left.mult * node.mult) % MOD;
		right.mult = ((ll)right.mult * node.mult) % MOD;

		left.add = ((ll)left.add * node.mult + node.add) % MOD;
		right.add = ((ll)right. add * node.mult + node.add) %MOD;
	}

	node.mult = 1;
	node.add = 0;
}

int update(int root, int start, int end, int left, int right, ll a, ll b){
	propagate(root, start, end);

	if (right < start || end < left) return root; 

	int nidx = add_node(root);
	Node &ret = nodes[nidx]; 

	if (left <= start && end <= right){
		ret.mult = (a * ret.mult) % MOD;
		ret.add = (ret.add * a + b) % MOD;
		propagate(nidx, start, end);
		return nidx;
	}

	int mid = (start + end) / 2;
	ret.left = update(ret.left, start, mid, left, right, a, b);
	ret.right = update(ret.right, mid + 1, end, left, right, a, b);
	ret.val = ((ll)nodes[ret.left].val + nodes[ret.right].val) % MOD;
	return nidx;
}

ll query(int root, int start, int end, int left, int right) {
	propagate(root, start, end);
	Node &node = nodes[root];
	if (right < start || end < left) return 0; 
	if (left <= start && end <= right) return node.val;

	int mid = (start + end) / 2;
	return (query(node.left, start, mid, left, right) + query(node.right, mid + 1, end, left, right)) % MOD;
}

int init(vector<int>& A, int start, int end) {
	int nidx = add_node();
	Node &node = nodes[nidx];

	if (start == end) node.val = A[start];
	else {
		int mid = (start + end) / 2;
		node.left = init(A, start, mid);
		node.right = init(A, mid + 1, end);
		node.val = ((ll)nodes[node.left].val + nodes[node.right].val) % MOD;
	}

	return nidx;
}

int main() {
	fastio;
	int N, M;
	cin >> N >> M;

	nodes.reserve(1 << 25);

	vector<int> A(N + 1);
	nodes.emplace_back();

	for (int i = 1; i <= N; i++) cin >> A[i];

	int root[4];

	root[0] = init(A, 0, N);
	for (int i = 1; i < 4; i++) root[i] = root[0]; 

	int t, l, r, v;
	for (int i = 0; i < M; i++) {
		cin >> t >> l >> r >> v;

		if (t == 0) {//add
			int add = update(root[0], 0, N, l, r, 1, v);
			int mlt = update(root[1], 0, N, l, r, v, 0);
			int mod = root[(v + 3) % 4];

			root[0] = add;
			root[1] = mlt;
			root[3] = mod;
		}
		else if (t == 1) {//mult
			int mlt = update(root[0], 0, N, l, r, v, 0);
			int mod = root[(v + 2) % 4];
			int add = update(root[3], 0, N, l, r, 1, v);

			root[0] = mlt;
			root[2] = mod;
			root[3] = add;
		}
		else if (t == 2) {//query
			cout << query(root[0], 0, N, l, r) << '\n';
			int mod = root[(v + 1) % 4];
			int add = update(root[2], 0, N, l, r, 1, v);
			int mlt = update(root[3], 0, N, l, r, v, 0);

			root[1] = mod;
			root[2] = add;
			root[3] = mlt;
		}
		else {//modify
			int mod = root[v % 4];
			int add = update(root[1], 0, N, l, r, 1, v);
			int mlt = update(root[2], 0, N, l, r, v, 0);

			root[0] = mod;
			root[1] = add;
			root[2] = mlt;
		}
	}
}