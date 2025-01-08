#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int INF = 1e9;

int N;
int source, sink;

vector<int> start_time, end_time;
vector<vector<int>> adj, cap, flow, cost;

int MCMF() {
	int ans = 0;
	int mf = 0;
	
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

		mf += f;
	}

	return mf == N ? ans : -1;
}

void init() {
	source = 0, sink = 2 * N + 1;
	start_time.resize(N + 1);
	end_time.resize(N + 1);

	adj.resize(2 * N + 2);
	cap.resize(2 * N + 2, vector<int>(2 * N + 2));
	flow.resize(2 * N + 2, vector<int>(2 * N + 2));
	cost.resize(2 * N + 2, vector<int>(2 * N + 2));
}

int main() {
	fastio;

	cin >> N;

	init();

	for (int i = 1; i <= N; i++) cin >> start_time[i];
	for (int i = 1; i <= N; i++) cin >> end_time[i];

	int T, F;
	cin >> T >> F;

	for (int i = 1; i <= N; i++) {
		adj[source].emplace_back(i);
		adj[i].emplace_back(source);

		adj[i + N].emplace_back(sink);
		adj[sink].emplace_back(i + N);

		cap[source][i] = 1;
		cap[i + N][sink] = 1;

		for (int j = 1; j <= N; j++) {
			int s = end_time[i] - start_time[j];

			if (s > 0) {
				adj[i].emplace_back(j + N);
				adj[j + N].emplace_back(i);

				cap[i][j + N] = 1;

				if (s < T) {
					int c = (T - s);
					c *= c;

					c = min(c, F);

					cost[i][j + N] = c;
					cost[j + N][i] = -c;
				}
			}

		}
	}

	int ans = MCMF();
	cout << ans << ' ';

	if (ans >= 0) {
		for (auto &v : flow) {
			for (auto &f : v) f = 0;
		}

		for (auto &v : cost) {
			for (auto &c : v) c = -c;
		}
	
		cout << -MCMF();
	}

}