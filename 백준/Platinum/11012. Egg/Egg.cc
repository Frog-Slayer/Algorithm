#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
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
	map<int, int> root;

	PST(int N, int Q): N(N) { 
		nodes.reserve(4 * N + 18 * Q);
	}

	int copy_node(const Node& node) {
		nodes.emplace_back(node);
		return nodes.size() - 1;
	}

	int make_node() {
		nodes.emplace_back();
		return nodes.size() - 1;
	}

	int init(int start, int end) {
		int node = make_node();

		if (start == end)  return node;
	
		int mid = (start + end) / 2;
		nodes[node].left = init(start, mid);
		nodes[node].right = init(mid + 1, end);

		return node;
	}

	void init() {
		root[0] = init(0, N - 1);
	}	

	int update(int node, int start, int end, int idx) {
		node = copy_node(nodes[node]);

		if (start == end) {
			nodes[node].val++;
			return node;
		}

		int mid = (start + end) / 2;

		if (idx <= mid) nodes[node].left = update(nodes[node].left, start, mid, idx);
		else nodes[node].right = update(nodes[node].right, mid + 1, end, idx);
		
		nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;

		return node;
	}

	void update(int version, int idx) {
		root[version] = update(root.rbegin()->second, 0, N - 1, idx);
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

	int T;
	cin >> T;

	while (T--) {
		int N, M;
		cin >> N >> M;

		vector<pair<int, int>> points(N);
		vector<int> xx, yy;

		for (int i = 0; i < N; i++) {
			cin >> points[i].first >> points[i].second;
			xx.emplace_back(points[i].first);
			yy.emplace_back(points[i].second);
		}
		
		sort(all(points));

		auto compress = [](vector<int> &v) {
			sort(all(v));
			v.erase(unique(all(v)), v.end());
		};

		compress(xx); compress(yy);
	
		PST pst(100001, N);
		pst.init();

		for (int i = 0, j = 0; i < N; i = j) {
			while (j < N && points[i].first == points[j].first) j++;

			for (int k = i; k < j; k++) {
				auto &[x, y] = points[k];
				x = lower_bound(all(xx), x) - xx.begin();
				pst.update(x, y);
			}
		}

		ll ans = 0;
		for (int i = 0; i < M; i++) {
			int l, r, b, t;
			cin >> l >> r >> b >> t;

			l = lower_bound(all(xx), l) - xx.begin() - 1;
			r = upper_bound(all(xx), r) - xx.begin() - 1;

			ans += pst.query(r, b, t) - (l >= 0 ? pst.query(l, b, t) : 0);
		}

		cout << ans << '\n';
	}
}