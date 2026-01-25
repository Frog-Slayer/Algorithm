#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int N, M;
string yokohama = "YOKOHAMA";
vector<string> board;
vector<int> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};

int dfs(int i, int x, int y) { 
	if (i == 7) return 1;

	int ret = 0;

	for (int d = 0; d < 4; d++) { 
		int nx = x + dx[d], ny= y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;

		if (board[nx][ny] == yokohama[i + 1]) { 
			ret += dfs(i + 1, nx, ny);
		}
	}

	return ret;
}

int main() { 
	fastio;

	cin >> N >> M;

	board.resize(N);

	for (int i = 0; i < N; i++) { 
		cin >> board[i];
	}

	int ans = 0;

	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < M; j++) if (board[i][j] == 'Y') ans += dfs(0, i, j);
	}


	cout << ans;

}
