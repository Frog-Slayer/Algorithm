#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

struct Union_Find {
	vector<int> parent;

	Union_Find(int N) : parent(N + 1) {
		clear();
	}

	void clear() {
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
	vector<int> tree;

	Segtree(int N) : tree(4 * N) {}

	void update(int node, int start, int end, int idx, int v) {
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] = v;
			return;
		}

		int mid = (start + end) / 2;
		if (idx <= mid) update(node * 2, start, mid, idx, v);
		else update(node * 2 + 1, mid + 1, end, idx, v);

		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	int query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return 0; 
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

	void update(int u, int w) {
		tree.update(1, 0, N - 1, in[u], w);
	}

	int query(int u, int v) {
		int ret = 0;

		while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            int start = top[u];
            ret += tree.query(1, 0, N - 1, in[start], in[u]);
            u = parent[start];
		}

		if (depth[u] > depth[v]) swap(u, v);
		ret += tree.query(1, 0, N - 1, in[u], in[v]);

		return ret;
	}
};

int main() {
	fastio;

	int N;
	cin >> N;

	HLD hld(N);
	Union_Find uf(N);

	vector<int> penguin(N + 1);

	for (int i = 1; i <= N; i++) cin >> penguin[i];

	int Q;
	cin >> Q;

	vector<tuple<int, int, int>> queries;

	for (int i = 0; i < Q; i++) {
		string op;
		int a, b;

		cin >> op >> a >> b;

		if (op[0] == 'b'){//bridge
			queries.emplace_back(0, a, b);
			if (uf.unionn(a, b)) { 
				hld.adj[a].emplace_back(b);
				hld.adj[b].emplace_back(a);
			}
		}
		else if (op[0] == 'p') queries.emplace_back(1, a, b);//penguins
		else queries.emplace_back(2, a, b);//excursion
	}

	for (int i = 2; i <= N; i++) {
		if (uf.unionn(1, i)) hld.adj[1].emplace_back(i);
	}


	hld.dfs();
	hld.euler_tour();
	uf.clear();

	for (int i = 1; i <= N; i++) hld.update(i, penguin[i]);

	for (auto &[op, a, b] :queries) {
		if (op == 0) {
			if (uf.unionn(a, b)) cout << "yes\n";
			else cout << "no\n";
		}
		else if (op == 1) hld.update(a, b);
		else {
			if (uf.find(a) == uf.find(b)) cout << hld.query(a, b) << '\n';
			else cout << "impossible\n";
		}
	}

	
}