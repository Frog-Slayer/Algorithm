#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int dist[101][101];

int main() { 
	fastio;

	int N;
	cin >> N;

	for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) { 
		if (i == j) continue;
		dist[i][j] = 999;
	}

	for (int i = 1; i < N; i++) { 
		int M;
		cin >> M;

		for (int j = 0; j < M; j++) { 
			int c;
			cin >> c;

			dist[i][c] = -1;
		}
	}

	for (int k = 1; k <= N; k++) { 
		for (int i = 1; i <= N; i++) { 
			for (int j = 1; j <= N; j++) { 
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	bool has_cycle = false;

	for (int i = 1; i <= N; i++) { 
		if (dist[1][i] <= 0 && dist[i][i] < 0) has_cycle = true;
	}

	cout << (has_cycle ? "CYCLE" : "NO CYCLE");
}