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
    vector<vector<pair<int, int>>> adj;
    vector<int> sz, depth, top, in, parent, e2v;
    vector<int> tree;

    HLD_Seg(int N) : N(N), sz(N + 1), depth(N + 1), top(N + 1), adj(N + 1), in(N + 1), parent(N + 1), e2v(N - 1), tree(4 * N + 4) {
        idx = 0;
    }

    void dfs(int cur = 1) {  // Subtree size calculation
        sz[cur] = 1;
        for (auto &p : adj[cur]) {
            auto &[next, edge_idx] = p;
            if (next == parent[cur]) continue;

            e2v[edge_idx] = next;  // Map edge to child node
            depth[next] = depth[cur] + 1;
            parent[next] = cur;

            dfs(next);

            sz[cur] += sz[next];
            if (sz[next] > sz[adj[cur][0].first]) swap(p, adj[cur][0]);
        }
    }

    void euler_tour(int cur = 1) {  // Euler tour for HLD
        in[cur] = idx++;
        for (auto &p : adj[cur]) {
            auto &[next, edge_idx] = p;
            if (next == parent[cur]) continue;

            if (adj[cur][0].first == next) top[next] = top[cur];  // Heavy edge
            else top[next] = next;                                // Light edge

            euler_tour(next);
        }
    }

    void update(int node, int start, int end, int idx, int val) {
        if (idx < start || end < idx) return;

        if (start == end) {
            tree[node] = val;
            return;
        }

        int mid = (start + end) / 2;
        update(node * 2, start, mid, idx, val);
        update(node * 2 + 1, mid + 1, end, idx, val);

        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int edge, int cost) {
        update(1, 0, N - 1, in[e2v[edge]], cost);
    }

    int query(int node, int start, int end, int left, int right) {
        if (right < start || end < left) return 0;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) / 2;
        return max(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
    }

    int query(int u, int v) {
        int ret = 0;

        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            int start = top[u];
            ret = max(ret, query(1, 0, N - 1, in[start], in[u]));
            u = parent[start];
        }

        if (u != v) {  // Exclude LCA itself
            if (depth[u] > depth[v]) swap(u, v);
            ret = max(ret, query(1, 0, N - 1, in[u] + 1, in[v]));
        }

        return ret;
    }
};

int main() {
    fastio;

    int N;
    cin >> N;

    HLD_Seg hld(N);
    vector<int> costs(N - 1);

    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        hld.adj[u].emplace_back(v, i);
        hld.adj[v].emplace_back(u, i);
        costs[i] = w;
    }

    hld.dfs();
    hld.euler_tour();

    for (int i = 0; i < N - 1; i++) hld.update(i, costs[i]);

    int M;
    cin >> M;

    for (int i = 0; i < M; i++) {
        int op, u, v;
        cin >> op >> u >> v;

        if (op == 1) {  // Update edge weight
            hld.update(--u, v);
        } else {  // Query max cost on the path
            cout << hld.query(u, v) << '\n';
        }
    }
}