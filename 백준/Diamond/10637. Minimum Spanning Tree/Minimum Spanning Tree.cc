#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;
const int INF = 1e9 + 7;

struct Union_Find {
	vector<int> parent;

	Union_Find(int N) : parent(N + 1) {
		for (int i = 0; i < parent.size(); i++) parent[i] = i;
	}

	int find(int a) {
		if (parent[a] == a) return a;
		return parent[a] = find(parent[a]);
	}

	bool unionn(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		parent[a] = b;
		return true;
	}
};

struct Segtree {
	vector<int> tree, lazy;
	Segtree(int N) : tree(4 * N, INF), lazy(4 * N, INF) {}

	void propagate(int node, int start, int end) {
		tree[node] = min(tree[node], lazy[node]);

		if (start != end) {
			for (int child : {node * 2, node * 2 + 1}) {
				lazy[child] = min(lazy[child], lazy[node]);
			}
		}
	}

	void update(int node, int start, int end, int left, int right, int v) {
		propagate(node, start, end);
		if (right < start || end < left) return;
		if (left <= start && end <= right) {
			lazy[node] = v;
			propagate(node, start, end);
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, v);
		update(node * 2 + 1, mid + 1, end, left, right, v);

		tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	}

	int query(int node, int start, int end, int left, int right) {
		propagate(node, start, end);
		if (right < start || end < left) return INF; 
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return min(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
	}
};

struct HLD {
	int N;
	int idx;
	vector<vector<int>> adj;
	vector<int> sz, depth, parent, in, top;
	Segtree tree;

	HLD(int N): N(N), adj(N + 1), sz(N + 1), depth(N + 1), parent(N + 1), in(N + 1), top(N + 1), tree(N), idx(-1) {}

	void dfs(int cur = 1) {
		sz[cur] = 1;

		for (auto &next : adj[cur]) {
			if (next == parent[cur]) continue;

			parent[next] = cur;
			depth[next] = depth[cur] + 1;

			dfs(next);

			sz[cur] += sz[next];

			if (sz[next] > sz[adj[cur][0]]) swap(next, adj[cur][0]);
		}
	}

	void euler_tour(int cur = 1) {
		in[cur] = ++idx;

		for (auto &next : adj[cur]) {
			if (next == parent[cur]) continue;

			if (next == adj[cur][0]) top[next] = top[cur];//heavy
			else top[next] = next;//light

			euler_tour(next);
		}
	}

	void update(int u, int v, int w) {
		while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
			tree.update(1, 0, N - 1, in[top[u]], in[u], w);
            u = parent[top[u]];
		}

		if (depth[u] > depth[v]) swap(u, v);
		tree.update(1, 0, N - 1, in[u] + 1, in[v], w);
	}

	int query(int u, int v) {
		int ret = INF;

		while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            ret = min(ret, tree.query(1, 0, N - 1, in[top[u]], in[u]));
            u = parent[top[u]];
		}

		if (depth[u] > depth[v]) swap(u, v);
		ret = min(ret, tree.query(1, 0, N - 1, in[u] + 1, in[v]));

		return ret;
	}
};

int main() {
	fastio;

	int N, M;
	cin >> N >> M;

	vector<tuple<int, int, int>> edges;
	vector<bool> in_mst(M + 1);
	priority_queue<pair<int, int>> pq;
	Union_Find uf(M);

	int mcnt = 0;
	ll mcost = 0;

	for (int i = 0; i < M; i++) {
		int a, b, w;
		cin >> a >> b >> w;
		edges.emplace_back(a, b, w);
		pq.emplace(-w, i);
	}

	while (!pq.empty()) {
		pair<int, int> top = pq.top();
		pq.pop();

		auto &[a, b, w] = edges[top.second];

		if (uf.unionn(a, b)){
			in_mst[top.second] = true;
			mcost += w;
			mcnt++;
		}
	}

	HLD hld(N);

	for (int i = 0; i < M; i++) {
		if (!in_mst[i]) continue;

		auto &[a, b, w] = edges[i];
		hld.adj[a].emplace_back(b);
		hld.adj[b].emplace_back(a);
	}

	hld.dfs();
	hld.euler_tour();

	for (int i = 0; i < M; i++) {
		if (in_mst[i]) continue;
		auto &[a, b, w] = edges[i];
		hld.update(a, b, w);
	}

	for (int i = 0; i < M; i++) {
		if (mcnt != N - 1) cout << -1 << '\n';
		else {
			if (!in_mst[i]) cout << mcost << '\n';
			else {
				auto &[a, b, w] = edges[i];
				int q = hld.query(a, b);
				if (q == INF) cout << -1 << '\n';
				else cout << mcost - w + q << '\n';
			}
		}
	}

}
