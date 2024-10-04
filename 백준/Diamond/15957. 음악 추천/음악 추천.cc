#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define fastio cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;
struct Segtree{
	int N;
	vector<ll> tree, lazy;

	void resize(int _N) {
		N = _N;
		tree.resize(4 * N);
		lazy.resize(4 * N);
	}

	void clear() {
		for (int i = 0; i < 4 * N; i++) tree[i] = lazy[i] = 0;
	}

	void propagate(int node, int start, int end) {
		tree[node] += (end - start + 1) * lazy[node];

		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}

		lazy[node] = 0;
	}

	void update(int node, int start, int end, int left, int right, int val) {
		propagate(node, start, end);
		if (right < start || end < left) return;
		if (left <= start && end <= right) {
			lazy[node] += val;
			propagate(node, start, end);
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, val);
		update(node * 2 + 1, mid + 1, end, left, right, val);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	ll query(int node, int start, int end, int idx) {
		propagate(node, start, end);
		if (idx < start || end < idx) return 0;
		if (start == end) return tree[node];

		int mid = (start + end) / 2;
		return query(node * 2, start, mid, idx) + query(node * 2 + 1, mid + 1, end, idx);
	}
} tree;

vector<pair<int, int>> range;
vector<vector<int>> adj;	
vector<int> sz;
int idx = 0;

int init(int node){
	range[node].first = ++idx;
	sz[node] = 1;
	for (int child : adj[node]){
		sz[node] += init(child);
	}
	range[node].second = idx;

	return sz[node];
}

int main() {
	fastio;
	ll N, K, J;

	cin >> N >> K >> J;

	sz.resize(N + 1);
	range.resize(N + 1);
	adj.resize(N + 1);
	tree.resize(N + 1);
	vector<int> singer_of_song(N + 1);
	vector<vector<int>> song_of_singer(N + 1);
	vector<pair<int, int>> pbs(N + 1);
	vector<tuple<int, int, int>> queries;

	for (int i = 2; i <= N; i++) {
		int parent;
		cin >> parent;
		adj[parent].emplace_back(i);
	}

	init(1);

	for (int i = 1; i <= N; i++) {
		int s;
		cin >> s;
		singer_of_song[i] = s;
		song_of_singer[s].emplace_back(i);
		pbs[s] = {0, K - 1};
	}

	for (int i = 0; i < K; i++) {
		int T, P, S;
		cin >> T >> P >> S;
		queries.emplace_back(T, P, S);
	}

	sort(all(queries));

	bool flag = true;

	vector<int> ans(N + 1, -1);

	while (flag) {
		flag = false;
		tree.clear();
		map<int, vector<int>> tasks;

		for (int i = 1; i <= N; i++) {
			if (!song_of_singer[i].size() || pbs[i].first >= pbs[i].second) continue;
			int m = pbs[i].first + pbs[i].second >> 1;
			tasks[m].emplace_back(i);
			flag = true;
		}

		for (int i = 0; i < K; i++) {
			auto &[T, P, S] = queries[i];
			tree.update(1, 1, N, range[P].first, range[P].second, S / sz[P]);

			for (auto &j : tasks[i]) {
				ll sum = 0;
				for (auto &song : song_of_singer[j]) sum += tree.query(1, 1, N, range[song].first);

				if (sum > song_of_singer[j].size() * J) {
					pbs[j].second = i;
					ans[j] = T;
				}
				else pbs[j].first = i + 1;
			}
		}
	}

	for (int i = 1; i <= N; i++) cout << ans[singer_of_song[i]] << '\n';
}