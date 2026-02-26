#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

void solve(int H, int W, int S, int L) { 
	map<tuple<int, int, int>, int> m;
	queue<pair<int, int>> q;

	vector<vector<int>> v(H, vector<int>(W));
	vector<vector<bool>> visited(H, vector<bool>(W));

	vector<int> dx = {0, 0, 1, -1, 1, 1, -1, -1};
	vector<int> dy = {1, -1, 0, 0, 1, -1, 1, -1};

	for (int i = 0; i < H; i++) { 
		for (int j = 0; j < W; j++) { 
			int R, G, B;
			cin >> R >> G >> B;

			R /= S;
			G /= S;
			B /= S;

			tuple<int, int, int> t = {R, G, B};

			if (m.find(t) == m.end()) m.emplace(t, m.size() + 1); 

			v[i][j] = m[t];
		}
	}


	auto bfs = [&](int color) -> int { 
		int cnt = 0;

		while (!q.empty()) { 
			auto [x, y] = q.front();
			q.pop();

			cnt++;

			for (int d = 0; d < 8; d++) { 
				int nx = x + dx[d];
				int ny = y + dy[d];

				if (nx < 0 || ny < 0 || nx >= H || ny >= W) continue;
				if (v[nx][ny] != color) continue;
				if (visited[nx][ny]) continue;

				visited[nx][ny] = true;
				q.emplace(nx, ny);
			}
		}

		return cnt;
	};

	int ans = 0;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) { 
			if (visited[i][j]) continue;
			q.emplace(i, j);
			visited[i][j] = true;
			if (bfs(v[i][j]) >= L) ans++;
		}
	}

	cout << ans << '\n';
}

int main() { 
	fastio;

	while (true) { 
		int H, W, S, L;
		cin >> H >> W >> S >> L;

		if (!H && !W && !S && !L) break;
		solve(H, W, S, L);
	}
}
