#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
using namespace std;

const int INF = 99999999;
const int MAX_K = 100;
const int MAX_N = 500000;
int K, N;
vector<double> angles;
vector<pair<double, double>> vd;
int dp[MAX_K + 1][MAX_N * 2+ 1];

struct Node {
	int sum;
	int mn = INF;
	
	Node operator+(const Node &rhs) {
		return { sum + rhs.sum, min(mn, rhs.mn) };
	}
};

struct Segtree {
	vector<Node> tree, lazy;
	int N;

	void resize(int _N) {
		N = _N;
		tree.resize(4 * N + 4);
		lazy.resize(4 * N + 4);
	}

	void propagate(int node, int start, int end) {

		tree[node].sum += lazy[node].sum;
		tree[node].mn = min(tree[node].mn, lazy[node].mn);

		if (start != end) {
			for (int i : { node * 2, node * 2 + 1}) {
				lazy[i].sum += lazy[node].sum;
				lazy[i].mn = min(lazy[i].mn, lazy[node].mn);
			}
		}

		lazy[node].sum = 0;
		lazy[node].mn = INF;
	}

	void update(int node, int start, int end, int left, int right, int val) {
		propagate(node, start, end);
		if (right < start || end < left) return;
		if (left <= start && end <= right) {
			lazy[node] = { 1, val };
			propagate(node, start, end);
			return;
		}

		int mid = (start + end) >> 1;
		update(node * 2, start, mid, left, right, val);
		update(node * 2 + 1, mid + 1, end, left, right, val);
	
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	void update(int left, int right, int val) {
		update(1, 1, N, left, right, val);
	}

	Node query(int node, int start, int end, int left, int right) {
		propagate(node, start, end);
		if (right < start || end < left) return { 0,  INF};
		if (left <= start && end <= right) return tree[node]; 

		int mid = (start + end) >> 1;
		return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
	}

	Node query(int idx) {
		return query(1, 1, N, idx, idx);
	}
} segtree;

int main() {
	scanf("%d%d", &K, &N);

	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

		double a1 = atan2(y1, x1);
		double a2 = atan2(y2, x2);
		angles.emplace_back(a1);
		angles.emplace_back(a2);

		if (a1 > a2) swap(a1, a2);
		vd.emplace_back(a1, a2);
	}

	//압축
	sort(angles.begin(), angles.end());
	angles.erase(unique(angles.begin(), angles.end()), angles.end());
	sort(vd.begin(), vd.end());
	segtree.resize(angles.size());

	for (int i = 0; i < N; i++) {
		int first = lower_bound(angles.begin(), angles.end(), vd[i].first) - angles.begin() + 1;
		int second = lower_bound(angles.begin(), angles.end(), vd[i].second) - angles.begin() + 1;

		segtree.update(first, second, first);
	}

	int ans = 0;
	for (int i = 1; i <= angles.size(); i++) {
		Node q = segtree.query(i);

		for (int k = 1; k <= K; k++) {
			dp[k][i] = max(dp[k][i - 1], dp[k - 1][q.mn - 1] + q.sum);
			ans = max(ans, dp[k][i]);
		}
	}

	printf("%d", ans);
}