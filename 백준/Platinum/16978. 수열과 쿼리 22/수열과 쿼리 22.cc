#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

struct Node {
	ll val;
	int left, right;

	Node() : val(0), left(-1), right(-1) {} 

	Node(const Node &node) {
		val = node.val;
		left = node.left;
		right = node.right;
	}
};

struct PST{
	int N;
	vector<Node> nodes;
	vector<int> root;

	PST(int N, int Q): N(N) { 
		nodes.reserve(4 * N + 18 * Q);
		root.reserve(Q);
	}

	int copy_node(const Node& node) {
		nodes.emplace_back(node);
		return nodes.size() - 1;
	}

	int make_node() {
		nodes.emplace_back();
		return nodes.size() - 1;
	}

	int init(int node, int start, int end, vector<int> &v) {
		if (node < 0) node = make_node();

		if (start == end)  {
			nodes[node].val = v[start];
			return node;
		}
	
		int mid = (start + end) / 2;
		nodes[node].left = init(nodes[node].left, start, mid, v);
		nodes[node].right = init(nodes[node].right, mid + 1, end, v);

		nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
		return node;
	}

	void init(vector<int> &v) {
		root.emplace_back(init(-1, 0, N - 1, v));
	}

	int update(int node, int start, int end, int idx, int val) {
		node = copy_node(nodes[node]);

		if (start == end) {
			nodes[node].val = val;
			return node;
		}

		int mid = (start + end) / 2;

		if (idx <= mid) nodes[node].left = update(nodes[node].left, start, mid, idx, val);
		else nodes[node].right = update(nodes[node].right, mid + 1, end, idx, val);
		
		nodes[node].val = (nodes[node].left < 0 ? 0 : nodes[nodes[node].left].val) + (nodes[node].right < 0 ? 0 : nodes[nodes[node].right].val);

		return node;
	}

	void update(int idx, int val) {
		root.emplace_back(update(root.back(), 0, N - 1, idx, val));
	}

	ll query(int node, int start, int end, int left, int right) {
		if (node < 0 || right < start || end < left) return 0;
		if (left <= start && end <= right) return nodes[node].val; 

		int mid = (start + end) / 2;

		return query(nodes[node].left, start, mid, left, right) + query(nodes[node].right, mid + 1, end, left, right);
	}

	ll query(int version, int left, int right) {
		return query(root[version], 0, N - 1, left, right);
	}
};

int main() {
	fastio;

	int N;
	cin >> N;

	vector<int> A(N);
	for (int i = 0; i < N; i++) cin >> A[i];

	int M;
	cin >> M;

	vector<tuple<int, int>> upd;
	vector<tuple<int, int, int>> queries;
	
	for (int i = 0; i < M; i++) {
		int op;
		cin >> op;

		if (op == 1) {
			int idx, v;
			cin >> idx >> v;
			upd.emplace_back(idx, v);
		}
		else {
			int k, s, e;
			cin >> k >> s >> e;
			queries.emplace_back(k, s, e);
		}
	}

	PST pst(N, upd.size());
	pst.init(A);


	for (auto &[i, v]: upd) {
		i--;
		pst.update(i, v);
	}

	for (auto &[k, s, e] : queries) {
		s--; e--;
		cout << pst.query(k, s, e) << '\n';
	}

}