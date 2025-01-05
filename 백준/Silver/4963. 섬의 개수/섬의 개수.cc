#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	while (true) {
		int w, h;
		cin >> w >> h;

		if (!w) break;

		vector<vector<int>> map(h, vector<int>(w));
		vector<vector<bool>> visited(h, vector<bool>(w));
		vector<int> dx = {-1, -1, -1, 0, 0, 1, 1, 1}, dy = {-1, 0, 1, -1, 1, -1, 0, 1};

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> map[i][j];
			}
		}

		queue<pair<int, int>> q;
		int ans = 0;

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (visited[i][j]) continue;
				if (!map[i][j]) continue;

				q.emplace(i, j);
				visited[i][j] = true;
				++ans;

				while (!q.empty()) {
					auto [x, y] = q.front();
					q.pop();

					for (int d = 0; d < 8; d++) {
						int nx = x + dx[d], ny = y + dy[d];
						if (nx < 0|| ny < 0 || nx >= h || ny >= w) continue;
						if (visited[nx][ny]) continue;
						if (!map[nx][ny]) continue;
						visited[nx][ny] = true;
						q.emplace(nx, ny);
					}
				}
			}
		}

		cout << ans << '\n';
	}

	
}