#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

vector<int> dx = {0, 0, 1, -1}, dy = {-1, 1, 0, 0};

void solve(int tc, vector<vector<int>> &res) { 
	cout << "Case: " << tc << '\n';
	int h = res.size(), w = res[0].size();

	queue<pair<int, int>> q;

	if (!res[0][0]) { 
		res[0][0] = 1; 
		q.emplace(0, 0);
	}

	while (!q.empty()) { 
		auto [x, y] = q.front();
		q.pop();

		if (res[x][y] == -1) continue;

		for (int d = 0; d < 4; d++) { 
			int nx = x + dx[d], ny = y + dy[d];
			if (nx < 0 || ny < 0 || nx >= h || ny >= w) continue;
			if (res[nx][ny]) continue;
			res[nx][ny] = 1;
			q.emplace(nx, ny);
		}
	}

	for (int i = 0; i < h; i++) { 
		for (int j = 0; j < w; j++) cout << "+---";
		cout << "+\n";


		for (int j = 0; j < w; j++) { 
			cout << "| ";

			if (res[i][j] == 1) cout << "M ";
			else if (res[i][j] == -1) cout << "X ";
			else cout << "  "; 
		}
		cout << "|\n";
	}

	for (int j = 0; j < w; j++) cout << "+---";
	cout << "+\n";

	if (res[h - 1][w - 1] == 1) cout << "Minions can cross the room\n";
	else cout << "Minions cannot cross the room\n";
}

int main() { 
	fastio;

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) { 
		int h, w;
		cin >> h >> w;
		vector<string> v(h);

		vector<vector<int>> res(h, vector<int>(w, 0));

		for (int i = 0; i < h; i++) { 
			cin >> v[i];
			for (int j = 0; j < w; j++) if (v[i][j] == 'X') res[i][j] = -1;
		}

		solve(tc, res);
    }

}
