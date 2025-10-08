#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

vector<vector<int>> adj;
vector<bool> visited; 

bool dfs(int cur, int depth) {
	if (depth == 5) return true;

	for (int next : adj[cur]) { 
		if (visited[next]) continue;

		visited[next] = true;
		if (dfs(next, depth + 1)) return true;
		visited[next] = false;
	}

	return false;
}

int main () { 
	fastio;

	int N, M;
	cin >> N >> M;

	adj.resize(N), visited.resize(N);

	for (int i = 0; i < M; i++){ 
		int a, b;
		cin >> a >> b;

		adj[a].emplace_back(b);
		adj[b].emplace_back(a);
	}

	bool has_answer = false;

	for (int i = 0; i < N; i++) { 
		visited[i] = true;
		if (dfs(i, 1)) { 
			has_answer = true;
			break;
		}
		visited[i] = false;
	}

	cout << (has_answer ? 1 : 0);
}
