#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;
const ll INF = LONG_LONG_MAX;

int N, M;
vector<vector<pair<int, ll>>> edges;

bool is_reachable(int node) {

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.emplace(0, node);

	vector<ll> dist(N + 1, INF);
	dist[node] = 1;

	while (!pq.empty()) {
		auto [d, cur] = pq.top();
		pq.pop();

		for (auto &[next, w] : edges[cur]) {
			if (dist[next] > dist[cur] + 1) {
				dist[next] = dist[cur] + 1;
				pq.emplace(dist[next], next);
			}
		}
	}

	return dist[N] != INF;
}

int main() {
	fastio;

	cin >> N >> M;
	
	edges.resize(N + 1);
	vector<int> bt(N + 1);

	for (int i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		edges[u].emplace_back(v, -w);
	}

	vector<ll> dist(N + 1, INF);
	dist[1] = 0;

	for (int i = 0; i < N - 1; i++) {
		for (int s = 1; s <= N; s++) {
			for (auto &[e, w] : edges[s]) {
				if (dist[s] == INF) continue;
				if (dist[e] > dist[s] + w){
					dist[e] = dist[s] + w;
					bt[e] = s;
				}
			}
		}
	}

	bool has_cycle = false;
	for (int s = 1; s <= N; s++) {
		for (auto &[e, w] : edges[s]) {
			if (dist[s] == INF) continue;
			if (dist[e] > dist[s] + w && is_reachable(s)){
				has_cycle = true;
				break;
			}
		}
	}
	
	if (dist[N] == INF || has_cycle) cout << "-1";
	else {
		vector<int> path;
		int cur = N;

		while (cur != 1) {
			path.emplace_back(cur);
			cur = bt[cur];
		}

		path.emplace_back(1);

		for (int i = path.size() - 1; i >= 0; i--) cout << path[i] << ' ';



	}
}