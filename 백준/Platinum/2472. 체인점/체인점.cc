#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
using namespace std;

const int MAX_N = 100000;
const int INF = 1e9 + 7;

int N, A, B, C, M, T;
vector<vector<pair<int, int>>> adj;
vector<int> bb, tree;
vector<bool> ans;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

struct Node {
	int idx = 0, A = INF, B = INF, C = INF;

	bool operator<(Node &rhs) {
		if (A == rhs.A) return B > rhs.B;
		return A < rhs.A;
	}
};

vector<Node> v;

void dijk(int start) {
	if (start == A) v[start].A = 0;
	else if (start == B) {
		v[start].B = 0;
		bb.push_back(0);
	}
	else v[start].C = 0; 
	
	pq.push({0, start});

	while (!pq.empty()) {
		pair<int, int> top = pq.top();
		pq.pop();

		int dist = top.first, cur = top.second;

		for (pair<int, int> &a : adj[cur]) {
			int next = a.first, weight = a.second;

			if (start == A) {
				if (v[next].A <= dist + weight) continue;
				v[next].A = dist + weight;
				pq.push({v[next].A, next});
			}
			else if (start == B) {
				if (v[next].B <= dist + weight) continue;
				v[next].B = dist + weight;
				pq.push({v[next].B, next});
				bb.push_back(v[next].B);
			}
			else {
				if (v[next].C <= dist + weight) continue;
				v[next].C = dist + weight;
				pq.push({v[next].C, next});
			}
		}
	}
}

void update(int node, int start, int end, int idx, int val) {
	if (idx < start || end < idx) return;
	if (start == end) {
		tree[node] = min(tree[node], val);
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, idx, val);
	update(node * 2 + 1, mid + 1, end, idx, val);

	tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

int query(int node, int start, int end, int left, int right) {
	if (right < start || end < left) return INF;
	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	return min(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
}

int main(){
	scanf("%d", &N);

	adj.resize(N + 1);
	ans.resize(N + 1);
	v.resize(N + 1);

	for (int i = 1; i <= N; i++) v[i].idx = i;

	scanf("%d%d%d", &A, &B, &C);

	scanf("%d", &M);

	for (int x, y, z, i = 0; i < M; i++) {
		scanf("%d%d%d", &x, &y, &z);
		adj[x].emplace_back(y, z);
		adj[y].emplace_back(x, z);
	}

	dijk(A);
	dijk(B);
	dijk(C);

	sort(bb.begin(), bb.end());
	bb.erase(unique(bb.begin(), bb.end()), bb.end());
	tree = vector<int>(bb.size() * 4, INF);

	sort(v.begin() + 1, v.end());

	for (int i = 1; i <= N; i++) {
		int b = v[i].B;
		b = lower_bound(bb.begin(), bb.end(), b) - bb.begin();
		int q = query(1, 0, bb.size() - 1, 0, b - 1);
		if (q >= v[i].C) ans[v[i].idx] = true;
		update(1, 0, bb.size() - 1, b, v[i].C);
	}

	scanf("%d", &T);

	for (int q, t = 0; t < T; t++) {
		scanf("%d", &q);
		printf("%s\n", ans[q] ? "YES" : "NO");
	}
}