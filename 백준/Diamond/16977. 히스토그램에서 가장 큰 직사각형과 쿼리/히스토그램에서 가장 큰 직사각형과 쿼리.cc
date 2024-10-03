#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define fastio cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)); v.erase(unique(all(v)), v.end())

struct Node {
	int lmax = 0, rmax = 0, mx = 0, len = 0;
	Node *left = NULL, *right = NULL;

	Node() {}
	Node(int v) : lmax(v), rmax(v), mx(v) {}

	Node(Node &nd) {
		lmax = nd.lmax;
		rmax = nd.rmax;
		mx = nd.mx;
		len = nd.len;
		left = nd.left;
		right = nd.right;
	}

	Node operator+(const Node &nd) {
		Node ret;
		ret.lmax = max(lmax, lmax == len ? len + nd.lmax : 0);
		ret.rmax = max(nd.rmax == nd.len? rmax + nd.len : 0, nd.rmax);
		ret.len = len + nd.len;
		ret.mx = max({mx, nd.mx, ret.lmax, ret.rmax, rmax + nd.lmax});
		return ret;
	}
};

Node* init(int start, int end) {
	Node *ret = new Node();
	ret->len = (end - start + 1);
	if (start == end) return ret;

	int mid = (start + end) / 2;
	ret->left = init(start, mid);
	ret->right = init(mid + 1, end);
	return ret;
}

Node* update(Node* node, int start, int end, int idx) {
	if (idx < start || end < idx) return node;
	if (start == end){
		Node *ret = new Node(1);
		ret->len = 1;
		return ret; 
	}

	int mid = (start + end) / 2;

	Node *l = node->left, *r = node->right;

	if (idx <= mid) l = update(node->left, start, mid, idx);
	else r = update(node->right, mid + 1, end, idx);

	Node *ret = new Node((*l) + (*r));
	ret->left = l;
	ret->right = r;

	return ret;
}

Node query(Node *node, int start, int end, int left, int right) {
	if (right < start || end < left){
		Node ret;
		ret.len = (end - start + 1);
		return ret;
	}
	if (left <= start && end <= right) return *node; 

	int mid = (start + end) / 2;
	return query(node->left, start, mid, left, right) + query(node->right, mid + 1, end, left, right);
}

int main() {
	fastio;
	int N;
	cin >> N;

	vector<pair<int, int>> height(N);
	vector<int> hh;

	for (int i = 0; i < N; i++) {
		cin >> height[i].first;
		height[i].second = i;
		hh.emplace_back(height[i].first);
	}

	compress(hh);
	sort(all(height), greater<>());

	vector<Node*> root(hh.size());
	int last = hh.size() - 1; 
	root[last] = init(0, N - 1);
	
	for (auto &[h, i]: height) {
		h = lower_bound(all(hh), h) - hh.begin();
		root[h] = update(root[last], 0, N - 1, i);
		last = h;
	}

	int Q;
	cin >> Q;

	for (int i = 0; i < Q; i++) {
		int l, r, w;
		cin >> l >> r >> w;
		l--; r--;

		int lo = 0, hi = hh.size() - 1;
		int ans = 0;
		while (lo <= hi) {
			int mid = (lo + hi) / 2;
			int q = query(root[mid], 0, N - 1, l, r).mx;

			if (q >= w){
				ans = mid;
				lo = mid + 1; 
			}
			else hi = mid - 1;
		}
		cout << hh[ans] << '\n';
	}
}