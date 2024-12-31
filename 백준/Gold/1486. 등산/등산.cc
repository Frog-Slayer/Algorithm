#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int INF = 1111111;

int main() {
	fastio;

	int N, M, T, D;
	cin >> N >> M >> T >> D;

	vector<int> dx = {0, -1, 1, 0}, dy = {-1, 0, 0, 1};
	vector<int> height(N * M);

	for (int i = 0; i < N; i++){
		string s;
		cin >> s;

		for (int j = 0; j < M; j++) {
			if (s[j] >= 'a' && s[j] <= 'z') height[i * M + j] = s[j] - 'a' + 26; 
			else height[i * M + j] = s[j] - 'A';
		}
	}

	vector<vector<int>> dist(N * M, vector<int>(N * M, INF));

	for (int i = 0; i < N * M; i++) {
		int x = i / M, y = i % M;
		dist[i][i] = 0;

		for (int d = 0; d < 4; d++) {
			int nx = x + dx[d], ny = y + dy[d];
			if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;

			int j = nx * M + ny;
			int diff = height[i] - height[j];
			if (abs(diff) > T) continue;
			if (diff >= 0) dist[i][j] = 1;
			else dist[i][j] = diff * diff;
		}

	}

	for (int k = 0; k < N * M; k++) {
		for (int i = 0; i < N * M; i++) {
			for (int j = 0; j < N * M; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	int ans = 0;

	for (int i = 0; i < N * M; i++) {
		if (dist[0][i] + dist[i][0] <= D) ans = max(ans, height[i]);
	}

	cout << ans;


}