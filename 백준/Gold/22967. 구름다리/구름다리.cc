#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int MAX_N = 300;
const int INF = 90000;
bool adj[MAX_N + 1][MAX_N + 1];

int main() {
	fastio;

	int N;
	cin >> N;

	for (int i = 0; i < N - 1; i++) { 
		int a, b;
		cin >> a >> b;
		adj[a][b] = adj[b][a] = true;
	}

	vector<tuple<int, int>> edges;

	if (N <= 4) { 
		for (int i = 1; i <= N; i++) { 
			for (int j = i + 1; j <= N; j++) { 
				if (!adj[i][j]) edges.emplace_back(i, j);
			}
		}
	}
	else { 
		for (int i = 2; i <= N; i++) { 
			if (!adj[1][i]) edges.emplace_back(1, i);
		}
	}

	cout << edges.size() << '\n';
	cout << (N <= 4 ? 1 : 2) << '\n';
	for (auto [a, b] : edges) cout << a << ' ' << b << '\n';



	
}