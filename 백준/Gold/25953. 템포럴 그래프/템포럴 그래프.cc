#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int INF = 100000000;
int dist[2][10000];

int main() { 
	fastio;

	int N, T, M, s, e;
	cin >> N >> T >> M;
	cin >> s >> e;

	for (int i = 0; i < N; i++) dist[0][i] = INF;
	dist[0][s] = 0;

	for (int i = 1; i <= T; i++) { 
		for (int j = 0; j < N; j++) dist[i % 2][j] = dist[!(i % 2)][j];

		for (int j = 0; j < M; j++) { 
			int a, b, w;
			cin >> a >> b >> w;

			dist[i % 2][a] = min(dist[i % 2][a], dist[!(i % 2)][b] + w);
			dist[i % 2][b] = min(dist[i % 2][b], dist[!(i % 2)][a] + w);
		}
	}

	int ans = dist[T % 2][e];
	cout << (ans == INF? -1 : ans);

}
