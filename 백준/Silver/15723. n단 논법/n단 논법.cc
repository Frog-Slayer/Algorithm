#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

vector<vector<int>> adj(26);

bool dfs(int parent, int cur, int target) { 
	if (cur == target) return true;

	for (auto next : adj[cur]) { 
		if (next == parent) continue;
		if (dfs(cur, next, target)) return true;
	}

	return false;
}


int main() { 
	fastio;
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) { 
		string tokens[3];
		for (int j = 0; j < 3; j++) { 
			cin >> tokens[j];
		}

		int from = tokens[0][0] - 'a';
		int to = tokens[2][0] - 'a';

		adj[from].emplace_back(to);
	}

	int m;
	cin >> m;

	for (int i = 0; i < m; i++) { 
		string tokens[3];

		for (int j = 0; j < 3; j++) { 
			cin >> tokens[j];
		}

		int from = tokens[0][0] - 'a';
		int to = tokens[2][0] - 'a';

		cout << (dfs(-1, from, to) ? 'T' : 'F') << '\n';
	}
}