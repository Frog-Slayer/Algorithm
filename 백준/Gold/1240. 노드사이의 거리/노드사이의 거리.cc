#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int N, M;
vector<vector<pair<int, int>>> adj;

int solve(int a, int b) {
	queue<pair<int, int>> q;
	vector<bool> visited(N + 1, false);
	q.push({a, 0});
	
	while (!q.empty()) {
		auto [cur, dist] = q.front();
		q.pop();

		if (cur == b) return dist;

		for (auto &[next, d] : adj[cur]) {
			if (visited[next]) continue;
			visited[next] = true;
			q.push({next, dist + d});
		}
	}

	return -1;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	cin >> N >> M;
	adj.resize(N + 1);

	for (int i = 0; i < N - 1; i++) {
		int a, b, d;
		cin >> a >> b >> d;

		adj[a].emplace_back(b, d);
		adj[b].emplace_back(a, d);
	}

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		cout << solve(a, b) << '\n';
	}

}