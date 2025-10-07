#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
pair<int, int> parent[300][300];

pair<int, int> find(pair<int, int> p) { 
	if (parent[p.first][p.second] == p) return p;
	return parent[p.first][p.second] = find(parent[p.first][p.second]);
}

void merge(pair<int, int> p1, pair<int, int> p2) { 
	p1 = find(p1), p2 = find(p2);
	if (p1 == p2) return;
	parent[p1.first][p1.second] = p2;
}

int main () { 
	fastio;

	int N, M;
	cin >> N >> M;

	int m[300][300];

	vector<pair<int, int>> glacier, tmp;

	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < M; j++) { 
			cin >> m[i][j];
			parent[i][j] = {i, j};
			if (m[i][j]) glacier.emplace_back(i, j);
		}
	}

	int ans = 0;

	while (!glacier.empty()) { 
		tmp.clear();
		vector<int> amt(glacier.size());
		pair<int, int> front = glacier.front();

		for (int i = 0; i < glacier.size(); i++) {
			auto [x, y] = glacier[i];

			for (int d = 0; d < 4; d++) { 
				int nx = x + dx[d], ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;

				if (m[nx][ny]) merge({x, y}, {nx, ny});
				else amt[i]++;
			}
		}

		for (auto [x, y]: glacier) { 
			if (find(front) != find({x, y})) { 
				cout << ans;
				return 0;
			}
		}

		for (auto [x, y]: glacier) parent[x][y] = {x, y};


		for (int i = 0; i < glacier.size(); i++) { 
			auto [x, y] = glacier[i];
			m[x][y] = max(0, m[x][y] - amt[i]);
			if (m[x][y]) tmp.emplace_back(x, y);
		}

		swap(glacier, tmp);
		ans++;
	}

	cout << 0;


}
