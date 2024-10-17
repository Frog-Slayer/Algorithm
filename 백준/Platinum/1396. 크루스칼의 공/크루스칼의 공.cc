#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int MAX_N = 1e5;
int parent[MAX_N + 1], sz[MAX_N + 1];
int find(int a) { if (a == parent[a]) return a;
	return parent[a] = find(parent[a]);
}

void merge(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return;
	sz[a] = sz[b] = sz[a] + sz[b];
	parent[a] = b;
}

int main() {
	fastio;

	int N, M;
	cin >> N >> M;

	vector<tuple<int, int, int>> edges;
	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		edges.emplace_back(c, a, b);
	}

	int Q;
	cin >> Q;

	vector<pair<int, int>> pbs(Q), queries(Q), ans(Q);

	for (int i = 0; i < Q; i++) {
		int x, y;
		cin >> x >> y;

		queries[i] = {x, y};
		pbs[i] = {-1, M};
	}

	sort(all(edges));
	
	while (1) {
		bool flag = false;
		map<int, vector<int>> tasks;

		for (int i = 0; i < Q; i++) {
			auto &[s, e] = pbs[i];
			if (s + 1 == e) continue;
			tasks[(s + e) / 2].emplace_back(i);
			flag = true;
		}

		if (!flag) break;
		
		for (int i = 1; i <= N; i++) parent[i] = i, sz[i] = 1;

		for (int i = 0; i < M; i++) {
			auto &[c, a, b] = edges[i];
			merge(a, b);

			for (auto j: tasks[i]) {
				auto [x, y] = queries[j];
				x = find(x), y = find(y);

				if (x == y) {
					pbs[j].second = i;
					ans[j] = {c, sz[x]};
				}
				else pbs[j].first = i;
			}
		}
	}

	for (int i = 0; i < Q; i++) {
		if (pbs[i].second == M) cout << "-1\n";
		else cout << ans[i].first << ' ' << ans[i].second << '\n';
	}
}