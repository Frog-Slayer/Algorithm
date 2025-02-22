#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int INF = 1e9; 

struct Segtree {
	int N;
	vector<int> tree, lazy;
	
	Segtree(int N) : N(N), tree(4 * N + 4, INF), lazy(4 * N + 4, INF) {}

	void propagate(int node, int start, int end) {
		if (lazy[node] == INF) return;
		tree[node] = min(tree[node], lazy[node]);

		if (start != end) {
			lazy[node * 2] = min(lazy[node * 2], lazy[node]);
			lazy[node * 2 + 1] = min(lazy[node * 2 + 1], lazy[node]);
		}

		lazy[node] = INF;
	}

	void update(int node, int start, int end, int left, int right, int val) {
		propagate(node, start, end);

		if (right < start || end < left) return;
		if (left <= start && end <= right) {
			lazy[node] = val;
			propagate(node, start, end);
			return; 
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, val);
		update(node * 2 + 1, mid + 1, end, left, right, val);

		tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	}

	void update(int left, int right, int val) {
		update(1, 1, N, left, right, val);
	}

	int query(int node, int start, int end, int left, int right) {
		propagate(node, start, end);
		if (right < start || end < left) return INF;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;

		return min(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
	}

	int query(int idx) {
		return query(1, 1, N, idx, idx);
	}
};

vector<vector<pair<int, int>>> edges;
vector<int> dist_a, dist_b;

void dijkstra(vector<int>& dist, int st){
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.emplace(dist[st] = 0, st);

	while (!pq.empty()) {
		auto [di, cur] = pq.top();
		pq.pop();

		for (auto [next, w] : edges[cur]) {
			if (dist[next] > dist[cur] + w) pq.emplace(dist[next] = dist[cur] + w, next);
		}
	}
}

vector<int> parent_a, parent_b;
vector<int> path;

void dfs(vector<int> &parent, vector<int> &dist, int st) {
	stack<tuple<int, int, int>> stk;
	stk.emplace(st, 0, st);

	while (!stk.empty()){ 
		auto [cur, prev, idx] = stk.top();
		stk.pop();

		if (parent[cur]) continue;
		if (path[cur]) idx = cur;

		parent[cur] = idx;

		for (auto &[next, w]: edges[cur]) {
			if (next == prev) continue;
			if (dist[next] !=  dist[cur] + w) continue;
			if (!path[cur] && path[next]) continue;

			stk.emplace(next, cur, idx);
		}

	}
}

void init(int N) {
	edges.resize(N + 1);

	dist_a.resize(N + 1, INF);
	dist_b.resize(N + 1, INF);

	parent_a.resize(N + 1);
	parent_b.resize(N + 1);

	path.resize(N + 1);
}

int main() {
	fastio;

	int N, M, A, B;
	cin >> N >> M >> A >> B;

	init(N);

	for (int i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >> w;

		edges[u].emplace_back(v, w);
		edges[v].emplace_back(u, w);
	}

	int K;
	cin >> K;

	for (int i = 1; i <= K; i++) {
		int vi;
		cin >> vi;
		path[vi] = i;
	}

	dijkstra(dist_a, A); dijkstra(dist_b, B);
	dfs(parent_a, dist_a, A); dfs(parent_b, dist_b, B);

	Segtree tree(K);

	for (int i = 1; i <= N; i++) {
		for (auto &[next, w] : edges[i]) {
			if (path[i] && path[next] && (path[i] == path[next] + 1 || path[next] == path[i] + 1)) continue;

			int left = path[parent_a[i]], right = path[parent_b[next]];

			tree.update(left, right - 1, dist_a[i] + dist_b[next] + w);
		}
	}

	for (int i = 1; i < K; i++) {
		int ans = tree.query(i);
		cout << (ans == INF ? -1 : ans) << '\n';
	}
}
