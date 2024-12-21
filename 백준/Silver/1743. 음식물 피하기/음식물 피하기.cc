#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N, M, K;
	cin >> N >> M >> K;

	vector<vector<int>> v(N, vector<int>(M));
	vector<vector<bool>> visited(N, vector<bool>(M));
	vector<int> dx = {-1, 0, 0, 1}, dy = {0, -1, 1, 0};

	queue<pair<int, int>> q;

	for (int i = 0; i < K; i++) {
		int r, c;
		cin >> r >> c;

		v[--r][--c] = 1;
	}

	int idx = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (visited[i][j]) continue;
			if (!v[i][j]) continue;
			q.emplace(i, j);
			v[i][j] = ++idx;
			visited[i][j] = true;

			while (!q.empty()) {
				auto [x, y] = q.front();
				q.pop();

				for (int d = 0; d < 4; d++) {
					int nx = x + dx[d], ny = y + dy[d];
					if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
					if (!v[nx][ny]) continue;
					if (visited[nx][ny]) continue;
					v[nx][ny] = v[x][y];
					visited[nx][ny] = true;
					q.emplace(nx, ny);
				}
			}
		}
	}

	vector<int> cnt(idx + 1);

	int ans = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!v[i][j]) continue;
			ans = max(ans, ++cnt[v[i][j]]);
		}
	}


	cout << ans;

	
}