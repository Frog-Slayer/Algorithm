#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef unsigned long long ll;
const ll MOD = 1ULL << 32;

struct Segtree {
	int N;
    vector<ll> tree, mult, add;

	Segtree(int N): N(N), tree(4 * N), mult(4 * N, 1), add(4 * N, 0) {}

	void propagate(int node, int start, int end) {
		if (mult[node] == 1 && add[node] == 0) return;
		tree[node] *= mult[node];
		tree[node] %= MOD;

		tree[node] += add[node] * (end - start + 1); 
		tree[node] %= MOD;

		if (start != end) {
			for (int child : {node * 2, node * 2 + 1}) {
				mult[child] *= mult[node];
				mult[child] %= MOD;

				add[child] *= mult[node];
				add[child] %= MOD;

				add[child] += add[node];
				add[child] %= MOD;
			}
		}

		mult[node] = 1;
		add[node] = 0;
	}

    void update(int node, int start, int end, int left, int right, ll a, ll b) {
		propagate(node, start, end);
        if (right < start || end < left) return;
		if (left <= start && end <= right) {
			mult[node] *= a;
			mult[node] %= MOD;

			add[node] *= a;
			add[node] %= MOD;

			add[node] += b;
			add[node] %= MOD;

			propagate(node, start, end);
			return;	
		}

        int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, a, b);
        update(node * 2 + 1, mid + 1, end, left, right, a, b);

		tree[node] = tree[node * 2] + tree[node * 2 + 1];
		tree[node] %= MOD;
    }

	ll query(int node, int start, int end, int left, int right) {
		propagate(node, start, end);
        if (right < start || end < left) return 0;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) / 2;
        return (query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right)) % MOD;
    }
};


struct HLD_Seg {
    int N;
    int idx;
    vector<vector<int>> adj;
    vector<int> sz, depth, top, in, out, parent;
	Segtree tree;

    HLD_Seg(int N) : N(N), sz(N + 1), depth(N + 1), top(N + 1), adj(N + 1), in(N + 1), out(N + 1), parent(N + 1), idx(-1), tree(N) {}

	void build(){
		dfs();
		euler_tour();
	}

    void dfs(int cur = 1) {
        sz[cur] = 1;

        for (auto &next : adj[cur]) {
            if (next == parent[cur]) continue;

            depth[next] = depth[cur] + 1;
            parent[next] = cur;

            dfs(next);

            sz[cur] += sz[next];
            if (sz[next] > sz[adj[cur][0]]) swap(next, adj[cur][0]);
        }
    }

    void euler_tour(int cur = 1) {
        in[cur] = ++idx;
        for (auto &next : adj[cur]) {
            if (next == parent[cur]) continue;

			if (adj[cur][0] == next) top[next] = top[cur];
            else top[next] = next;

            euler_tour(next);
        }

		out[cur] = idx;
    }

	void update(int u, ll a, ll b) {
		tree.update(1, 0, N - 1, in[u], out[u], a, b);
	}

    void update(int u, int v, ll a, ll b) {
		while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            int start = top[u];

			//upd
			tree.update(1, 0, N - 1, in[start], in[u], a, b);

            u = parent[start];
        }

		if (depth[u] > depth[v]) swap(u, v);
		tree.update(1, 0, N - 1, in[u], in[v], a, b);
    }
	
	ll query(int u) {
		return tree.query(1, 0, N - 1, in[u], out[u]);
	}

    ll query(int u, int v) {
        ll ret = 0;

        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            int start = top[u];

			//query
			ret += tree.query(1, 0, N - 1, in[start], in[u]);
			ret %= MOD;
            u = parent[start];
        }

		if (depth[u] > depth[v]) swap(u, v);
		ret += tree.query(1, 0, N - 1, in[u], in[v]);
		ret %= MOD;
        return ret;
    }
};

int main() {
	fastio;

    int N, Q;
	cin >> N >> Q;

    HLD_Seg hld(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
		cin >> u >> v;

        hld.adj[u].emplace_back(v);
        hld.adj[v].emplace_back(u);
    }

	hld.build();

    for (int i = 0; i < Q; i++) {
		int op, x, y, v;
		cin >> op;

		switch (op) {
			case 1: cin >> x >> v; hld.update(x, 1, v); break;
			case 2: cin >> x >> y >> v; hld.update(x, y, 1, v); break;
			case 3: cin >> x >> v; hld.update(x, v, 0); break;
			case 4: cin >> x >> y >> v; hld.update(x, y, v, 0); break;
			case 5: cin >> x; cout << hld.query(x) << '\n'; break;
			case 6: cin >> x >> y; cout << hld.query(x, y) << '\n'; break;
		}
    }
}