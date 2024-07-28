#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;

const int MAX_N = 100000;
int N, M;

struct Segtree{
	vector<int> tree;

	Segtree() {}
	Segtree(vector<int> &v) {
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());

		tree.resize(v.size() * 4);
		for (int i = 0; i < v.size(); i++) update(1, 0, v.size() - 1, i, 1);
	}

	void update(int node, int start, int end, int idx, int val) {
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] = val;
			return;
		}
	
		int mid = (start + end) >> 1;
		update(node * 2, start, mid, idx, val);
		update(node * 2 + 1, mid + 1, end, idx, val);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	int find(int node, int start, int end, int val) {
		if (start == end) return start;

		int mid = (start + end) / 2;

		if (tree[node * 2] >= val) return find(node * 2, start, mid, val);
		return find(node * 2 + 1, mid + 1, end, val - tree[node * 2]);	
	}
};

vector<vector<int>> adj;
Segtree segs[MAX_N + 1];

void dfs(int cur) {

	if (!segs[cur].tree.size()) return;

	printf("%d ", cur);
	for (int &next : adj[cur]) {
		int top_idx_in_next = lower_bound(adj[next].begin(), adj[next].end(), cur) - adj[next].begin();
		segs[next].update(1, 0, adj[next].size() - 1, top_idx_in_next, 0);
	}

	int cnt;
	while (cnt = segs[cur].tree[1]) {
		int idx = segs[cur].find(1, 0, adj[cur].size() - 1, cnt % 2 ? cnt / 2 + 1 : 1);

		segs[cur].update(1, 0, adj[cur].size() - 1, idx, 0);

		int next = adj[cur][idx];
		dfs(next);
	}
}

int main() {
	scanf("%d%d", &N, &M);

	adj.resize(N + 1);
	
	for (int i = 0; i < M; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		if (a == b) continue;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	for (int i = 1; i <= N; i++) segs[i] = Segtree(adj[i]);

	dfs(1);
	
}