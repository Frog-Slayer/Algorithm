#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

vector<vector<pair<int, int>>> adj;
vector<bool> visited;
int S, E;

bool bfs(int cap) { 
	queue<int> q;
	q.emplace(S);
	visited[S] = true;

	fill(all(visited), false);

	while (!q.empty()) { 
		int cur = q.front();
		q.pop();

		for (auto [next, cost] : adj[cur]) { 
			if (cost >= cap && !visited[next]) {
				visited[next] = true;
				q.emplace(next);
			}
		}
	}

	if (visited[E]) return true;
	return false;
}

int main() {
	fastio;

	int N, M;
	cin >> N >> M;

	adj.resize(N + 1);
	visited.resize(N + 1);

	for (int i = 0; i < M; i++) { 
		int A, B, C;
		cin >> A >> B >> C;

		adj[A].emplace_back(B, C);
		adj[B].emplace_back(A, C);
	}

	cin >> S >> E;

	int ans = 0;

	int left = 1, right = 1000000000;

	while (left <= right) { 
		int mid = (left + right) / 2;

		if (bfs(mid)) { 
			ans = mid;
			left = mid + 1;
		}
		else right = mid - 1;
	}

	cout << ans;
}
