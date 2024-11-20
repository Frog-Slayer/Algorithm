#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

struct HLD_Seg {
    int N;
    int idx;
    vector<vector<int>> adj;
    vector<int> sz, depth, top, in, parent;
    vector<int> tree, lazy;

    HLD_Seg(int N) : N(N), sz(N + 1), depth(N + 1), top(N + 1), adj(N + 1), in(N + 1), parent(N + 1), tree(4 * N + 4), lazy(4 * N + 4), idx(0) {}

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
        in[cur] = idx++;
        for (auto &next : adj[cur]) {
            if (next == parent[cur]) continue;

            if (adj[cur][0] == next) top[next] = top[cur];
            else top[next] = next;

            euler_tour(next);
        }
    }

	void propagate(int node, int start, int end) {
		if (!lazy[node]) return;
		tree[node] += (end - start + 1) * lazy[node];

		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}

		lazy[node] = 0;
	}

    void update(int node, int start, int end, int left, int right) {
		propagate(node, start, end);
        if (right < start || end < left) return;
		if (left <= start && end <= right) {
			lazy[node]++;
			propagate(node, start, end);
			return;	
		}

        int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right);
        update(node * 2 + 1, mid + 1, end, left, right);

		tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void update(int u, int v) {
		while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            int start = top[u];

			update(1, 0, N - 1, in[start], in[u]);
            u = parent[start];
        }

		if (depth[u] > depth[v]) swap(u, v);
		update(1, 0, N - 1, in[u] + 1, in[v]);
    }

    int query(int node, int start, int end, int left, int right) {
		propagate(node, start, end);
        if (right < start || end < left) return 0;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) / 2;
        return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
    }

    int query(int u, int v) {
        int ret = 0;

        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            int start = top[u];
            ret += query(1, 0, N - 1, in[start], in[u]);
            u = parent[start];
        }

		if (depth[u] > depth[v]) swap(u, v);
		ret += query(1, 0, N - 1, in[u] + 1, in[v]);

        return ret;
    }
};

int main() {
	fastio;

    int N, M;
	cin >> N >> M;

    HLD_Seg hld(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
		cin >> u >> v;

        hld.adj[u].emplace_back(v);
        hld.adj[v].emplace_back(u);
    }

    hld.dfs();
    hld.euler_tour();

    for (int i = 0; i < M; i++) {
		char w;
		int u, v;

		cin >> w >> u >> v;

		if (w == 'P') hld.update(u, v);
		else cout << hld.query(u, v) << '\n';
    }
}