#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

typedef long long ll;
typedef pair<ll, ll> Result;
const int MAX_P = 200000;

Result operator+(const Result& r1, const Result& r2) {
	return { r1.first + r2.first, r1.second + r2.second };
}

Result operator-(const Result& r1, const Result& r2) {
	return { r1.first - r2.first, r1.second - r2.second };
}

struct Node {
	int cnt;
	ll val;
	int left, right;

	Node() : cnt(0), val(0), left(-1), right(-1) {} 

	Node(const Node &node) {
		cnt = node.cnt;
		val = node.val;
		left = node.left;
		right = node.right;
	}
};

struct PST{
	vector<Node> nodes;
	vector<int> root;

	PST(int Q): root(Q + 1) { 
		nodes.reserve(MAX_P * 4 + 19 * Q);
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
		root[0] = init(1, MAX_P);
	}	

	int update(int node, int start, int end, int idx) {
		node = copy_node(nodes[node]);

		nodes[node].cnt++;
		nodes[node].val += idx;

		if (start == end) return node;

		int mid = (start + end) / 2;

		if (idx <= mid) nodes[node].left = update(nodes[node].left, start, mid, idx);
		else nodes[node].right = update(nodes[node].right, mid + 1, end, idx);
		
		return node;
	}

	void update(int engineer, int potential) {
		root[engineer] = update(root[engineer - 1], 1, MAX_P, potential);
	}

	Result query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return Result(0, 0) ;
		if (left <= start && end <= right) return Result(nodes[node].cnt, nodes[node].val); 

		int mid = (start + end) / 2;

		return query(nodes[node].left, start, mid, left, right) + query(nodes[node].right, mid + 1, end, left, right);
	}

	Result query(int version, int left, int right) {
		return query(root[version], 1, MAX_P, left, right);
	}
};

int main() {
	fastio;
	
	int N;
	cin >> N;

	PST pst(N);
	pst.init();

	for (int i = 1; i <= N; i++) {
		int potential;
		cin >> potential;
		pst.update(i, potential);
	}

	int Q;
	cin >> Q;

	for (int i = 0; i < Q; i++) {
		int l, r, a, b, s;
		cin >> l >> r >> a >> b >> s;

		int left = a, right = b, lb = b + 1;
		int cnt = 0;
		ll sum = 0;

		while (left <= right) {
			int mid = (left + right) / 2;

			Result res = pst.query(r, mid, b) - pst.query(l - 1, mid, b);

			if (res.first * s <= res.second){
				right = mid - 1;
				if (mid < lb) {
					lb = mid;
					cnt = res.first;
					sum = res.second;
				}
			}
			else left = mid + 1;
		}

		int ans = cnt;

		if (lb > a) {
			lb--;
			left = 0, right = (pst.query(r, lb, lb) - pst.query(l - 1, lb, lb)).first;

			while (left <= right) {
				int mid = (left + right) / 2;

				if ((cnt + mid) * (ll)s <= (lb * mid) + sum) {
					ans = max(ans, cnt + mid);
					left = mid + 1;
				}
				else right = mid - 1;
			}
		}

		cout << ans << '\n';
	}

}