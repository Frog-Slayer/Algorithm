#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

struct Segtree {
	struct Node {
		int left = 0;
		int right = 0;
		int mx = 0;
		int sum = 0;

		Node() {}

		Node(int v) {
			left = right = mx = max(0, v);
			sum = v;
		}

		Node operator+(const Node& nd) {
			Node ret;

			ret.left = max({left, sum + nd.left});
			ret.right = max({right + nd.sum, nd.right});
			ret.sum = sum + nd.sum;
			ret.mx = max({ret.left, ret.right, mx, nd.mx, right + nd.left});

			return ret;
		}
	};

	const int NONE = 11111;
	vector<Node> tree;
	vector<int> lazy;

	Segtree(int N) : tree(4 * N), lazy(4 * N, NONE) {}

	void propagate(int node, int start, int end) {
		if (lazy[node] == NONE) return;

		tree[node] = Node((end - start + 1) * lazy[node]);

		if (start != end) {
			lazy[node * 2] = lazy[node];
			lazy[node * 2 + 1] = lazy[node];
		}

		lazy[node] = NONE;
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

		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	Node query(int node, int start, int end, int left, int right) {
		propagate(node, start, end);
		if (right < start || end < left) return Node();
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
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

		if (in[u] > in[v]) swap(u, v);
		tree.update(1, 0, N - 1, in[u], in[v], w);
	}

	int query(int u, int v) {
		Segtree::Node node1, node2;

		if (in[u] > in[v]) swap(u, v);

		while (top[u] != top[v]) {
			if (depth[top[u]] > depth[top[v]]) {
				node1 = tree.query(1, 0, N - 1, in[top[u]], in[u]) + node1;
				u = parent[top[u]];
			}
			else {
				node2 = tree.query(1, 0, N - 1, in[top[v]], in[v]) + node2;
				v = parent[top[v]];
			}
		}

		if (in[u] > in[v]) node1 = tree.query(1, 0, N - 1, in[v], in[u]) + node1;
		else node2 = tree.query(1, 0, N - 1, in[u], in[v]) + node2; 

		swap(node1.left, node1.right);

		return (node1 + node2).mx;
	}
};

int main() {
	fastio;

	int N;
	cin >> N;

	HLD hld(N);

	vector<int> weights(N);
	for (int i = 0; i < N; i++) cin >> weights[i];

	for (int i = 0; i < N - 1; i++) {
		int u, v;
		cin >> u >> v;
		hld.adj[u].emplace_back(v);
		hld.adj[v].emplace_back(u);
	}

	hld.dfs();
	hld.euler_tour();

	for (int i = 0; i < N; i++) hld.update(i + 1, i + 1, weights[i]);

	int M;
	cin >> M;

	for (int i = 0; i < M; i++) {
		int op, u, v, w;
		cin >> op;

		if (op == 1) {
			cin >> u  >> v;
			cout << hld.query(u, v) << '\n';
		}
		else {
			cin >> u >> v >> w;
			hld.update(u, v, w);
		}
	}
}