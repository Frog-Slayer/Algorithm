#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()
#define compressed(x) lower_bound(all(xx), x) - xx.begin();

typedef long long ll;
typedef pair<ll, ll> Point;

vector<Point> p1, p2;
vector<tuple<int, int, int>> v;
vector<int> xx;

struct Node {
	ll left = 0;
	ll right = 0;
	ll sum = 0;
	ll mx = 0;

	Node () {}

	Node(ll a) {
		sum = a;
		left = right = mx = max(0LL, a);
	}

	Node operator+(const Node &node) {
		Node ret;
		ret.sum = sum + node.sum;
		ret.left = max(left, sum + node.left);
		ret.right = max(right + node.sum, node.right);
		ret.mx = max({mx, node.mx, ret.left, ret.right, right + node.left});

		return ret;
	}
};

struct Segtree {
	int N;
	vector<Node> tree;

	void resize(int _N) {
		N = _N;
		tree.resize(4 * N);
	}

	void clear() {
		tree.clear();
		tree.resize(4 * N);
	}

	void update(int node, int start, int end, int left, int right, Node &nd) {
		if (right < start || end < left) return;
		if (start == end) {
			tree[node] = nd;
			return;
		}
	
		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, nd);
		update(node * 2 + 1, mid + 1, end, left, right, nd);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	void update(int idx, Node &nd) {
		update(1, 0, N - 1, idx, idx, nd);
	}

	ll query() {
		return tree[1].mx;
	}

} tree;

int main() {
	int N1;
	scanf("%d", &N1);

	for (int i = 0; i < N1; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		xx.emplace_back(x);
		p1.emplace_back(x, y);
	}

	int N2;
	scanf("%d", &N2);

	for (int i = 0; i < N2; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		xx.emplace_back(x);
		p2.emplace_back(x, y);
	}

	int c1, c2;
	scanf("%d%d", &c1, &c2);

	sort(all(xx));
	tree.resize(N1 + N2);

	for (int i = 0; i < N1; i++) v.emplace_back(p1[i].second, p1[i].first, c1);
	for (int i = 0; i < N2; i++) v.emplace_back(p2[i].second, p2[i].first, -c2);

	for (auto &[y, x, c] : v) x = compressed(x);

	sort(all(v));
	ll ans = 0;

	for (int i = 0, j = 0; i < N1 + N2; i = j) {
		tree.clear();
	
		for (int k = i; k < N1 + N2; k++) {
			auto &[y, x, c] = v[k];
			Node nd(c);
			tree.update(x, nd);
			if (k == (N1 + N2 -1) || get<0>(v[k]) != get<0>(v[k + 1])) ans = max(ans, tree.query());
		}

		while (j < N1 + N2 && get<0>(v[i]) == get<0>(v[j])) j++;
	}

	printf("%lld", ans);
}