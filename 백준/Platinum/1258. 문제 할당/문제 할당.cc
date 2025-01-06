#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int INF = 1e9;

int main() {
	fastio;

	int N;
	cin >> N;

	int source = 0, sink = 2 * N + 1;

	vector<vector<int>> adj(2 * N + 2);
	vector<vector<int>> cap(2 * N + 2, vector<int>(2 * N + 2));
	vector<vector<int>> flow(2 * N + 2, vector<int>(2 * N + 2));
	vector<vector<int>> cost(2 * N + 2, vector<int>(2 * N + 2));

	for (int i = 1; i <= N; i++) {
		adj[source].emplace_back(i);
		adj[i].emplace_back(source);

		adj[i + N].emplace_back(sink);
		adj[sink].emplace_back(i + N);

		cap[source][i] = 1;
		cap[i + N][sink] = 1;

		for (int j = 1; j <= N; j++) {
			int c;
			cin >> c;

			cost[i][j + N] = c;
			cost[j + N][i] = -c;

			adj[i].emplace_back(j + N);
			adj[j + N].emplace_back(i);

			cap[i][j + N] = 1;
		}
	}

	int ans = 0;

	while (true) {
		vector<int> parent(2 * N + 2, -1), dist(2 * N + 2, INF);
		vector<bool> visited(2 * N + 2, false);

		queue<int> q;
		q.push(source);
		dist[source] = 0;
		visited[source] = true;

		while (!q.empty()) {
			int cur = q.front();
			q.pop();

			visited[cur] = false;

			for (int next : adj[cur]) {
				int resid_cap = cap[cur][next] - flow[cur][next];
				if (resid_cap > 0 && dist[next] > dist[cur] + cost[cur][next]) {
					parent[next] = cur;
					dist[next] = dist[cur] + cost[cur][next];

					if (!visited[next]) {
						q.push(next);
						visited[next] = true;
					}
				}
			}
		}

		if (parent[sink] == -1) break;
		int f = INF;

		for (int i = sink; i != source; i = parent[i]) {
			int prev = parent[i];
			int resid_cap = cap[prev][i] - flow[prev][i];
			f = min(f, resid_cap);
		}

		for (int i = sink; i != source; i = parent[i]) {
			int prev = parent[i];
			flow[prev][i] += f;
			flow[i][prev] -= f;

			ans += f * cost[prev][i];
		}
	}

	cout << ans;
}