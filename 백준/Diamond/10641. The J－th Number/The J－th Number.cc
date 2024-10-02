#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define fastio cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)); v.erase(unique(all(v)), v.end())

typedef long long ll;
const int MAX_N = 1 << 19;

struct Segtree{
	int N;
	vector<ll> tree;
	vector<int> lazy, len;

	Segtree() {
		tree.resize(MAX_N << 1);
		lazy.resize(MAX_N << 1);
		len.resize(MAX_N << 1);
	}

	void init(vector<int> &tt) {
		N = tt.size() - 1;
		build(1, 0, N - 1, tt);
	}

	void build(int node, int start, int end, vector<int> &tt) {
		if (start == end) {
			len[node] = tt[start + 1] - tt[start];
			return;
		}

		int mid = (start + end) / 2;
		build(node * 2, start, mid, tt);
		build(node * 2 + 1, mid + 1, end, tt);
		len[node] = len[node * 2] + len[node * 2 + 1];
	}

	void clear() {
		fill(all(tree), 0);
		fill(all(lazy), 0);
	}

	void propagate(int node, int start, int end) {
		tree[node] += (ll)len[node] * lazy[node];

		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}

		lazy[node] = 0;
	}

	void update(int node, int start, int end, int left, int right) {
		propagate(node, start, end);
		if (right < start || end < left) return;
		if (left <= start && end <= right){
		 	lazy[node]++;	
			propagate(node, start, end);
			return;
		}

		int mid = (start + end) / 2;

		update(node * 2, start, mid, left, right);
		update(node * 2 + 1, mid + 1, end, left, right);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	void update(int left, int right) {
		update(1, 0, N - 1, left, right);
	}

	ll query(int node, int start, int end, int left, int right) {
		propagate(node, start, end);
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node]; 

		int mid = (start + end) / 2;
		return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
	}

	ll query(int left, int right) {
		return query(1, 0, N - 1, left, right);
	}
} tree;

int main() {
	fastio;

	int N, M, Q;

	cin >> N >> M >> Q;

	vector<int> vv, tt;
	vector<tuple<int, int, int>> updates;
	vector<tuple<int, int, ll>> queries;
	vector<pair<int, int>> pbs;

	for (int i = 0; i < M; i++) {
		int a, b, v;
		cin >> a >> b >> v;
		vv.emplace_back(v);
		tt.emplace_back(a);
		tt.emplace_back(b + 1);
		updates.emplace_back(v, a, b + 1);
	}


	for (int i = 0; i < Q; i++) {
		int x, y;
		ll j;
		cin >> x >> y >> j;
		queries.emplace_back(x, y + 1, j);
		tt.emplace_back(x);
		tt.emplace_back(y + 1);
	}

	compress(vv);
	compress(tt);
	tree.init(tt);

	for (auto &[v, a, b]: updates) {
		v = lower_bound(all(vv), v) - vv.begin();
		a = lower_bound(all(tt), a) - tt.begin();
		b = lower_bound(all(tt), b) - tt.begin();
	}

	for (auto &[x, y, j]: queries) {
		x = lower_bound(all(tt), x) - tt.begin();
		y = lower_bound(all(tt), y) - tt.begin();
		pbs.emplace_back(0, vv.size() - 1);
	}

	sort(all(updates));

	bool flag = true;
	vector<pair<int, int>> tasks;

	while (flag) {
		flag = false;
		tasks.clear();
		tree.clear();

		for (int i = 0; i < Q; i++) if (pbs[i].first < pbs[i].second) tasks.emplace_back((pbs[i].first + pbs[i].second) / 2, i);
		sort(all(tasks));

		int j = 0;

		for (auto &[m, i]: tasks) {
			while (j < M) {
				auto &[v, a, b] = updates[j];
				if (v > m) break;
				tree.update(a, b - 1);
				j++;
			}

			auto &[x, y, k] = queries[i];

			if (tree.query(x, y - 1) >= k) pbs[i].second = m;
			else pbs[i].first = m + 1;

			if (pbs[i].first < pbs[i].second) flag = true;
		}
	}

	for (int i = 0; i < Q; i++) cout << vv[pbs[i].first] << '\n';
}