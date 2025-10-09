#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int N;
int height[100][100];
int color[100][100];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

int solve(int h) { 
	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < N; j++) { 
			color[i][j] = 0;
		}
	}

	int k = 0;
	queue<pair<int, int>> q;

	auto bfs = [&]() { 
		while (!q.empty()) { 
			auto [x, y] = q.front();
			q.pop();

			for (int d = 0; d < 4; d++) { 
				int nx = x + dx[d], ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (height[nx][ny] <= h) continue;
				if (color[nx][ny]) continue;

				color[nx][ny] = color[x][y];
				q.emplace(nx, ny);
			}
		}
	};

	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < N; j++) { 
			if (height[i][j] > h && !color[i][j]) { 
				q.emplace(i, j);
				color[i][j] = ++k;
				bfs();
			}
		}
	}

	return k;
}

int main () { 
	fastio;

	cin >> N;


	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < N; j++) { 
			cin >> height[i][j];
		}
	}

	int ans = 0;

	for (int i = 0; i <= 100; i++) { 
		ans = max(ans, solve(i));
	}

	cout << ans;
	

}