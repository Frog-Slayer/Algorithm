#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

const int INF = 2555;
int dx[] = { -1, 0, 0, 1 }, dy[] = { 0, -1, 1, 0 };
int empt_count = 0, N, M;

int solve(vector<vector<int>> &lab, vector<pair<int, int>> &inactivated, int flag) {
	queue<pair<int, int>> q;
	vector<vector<int>> v(N, vector<int>(N));

	int cnt = empt_count;

	for (int i = 0; i < inactivated.size(); i++) {
		if (flag & (1 << i)){
			auto [x, y] = inactivated[i];
			q.emplace(x, y);
			v[x][y] = 1;
		}
	}

	int ret = -1;

	while (!q.empty()) {
		auto [x, y] = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;//out of range
			if (lab[nx][ny] == 1) continue;//wall
			if (v[nx][ny]) continue;//visited

			ret = v[nx][ny] = v[x][y] + 1;

			if (lab[nx][ny] == 0) cnt--;
			if (!cnt) return v[x][y]; 

			q.emplace(nx, ny);
		}
	}

	if (!cnt) return ret - 1;
	return INF;
}

int main() {
	fastio;

	cin >> N >> M;

	vector<vector<int>> lab(N, vector<int>(N));
	vector<pair<int, int>> inactivated;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> lab[i][j];
			if (lab[i][j] == 2) inactivated.emplace_back(i, j);
			else if (lab[i][j] == 0) empt_count++;
		}
	}

	int ans = INF; 
	if (empt_count == 0) cout << 0;
	else {
		for (int i = 1; i < (1 << inactivated.size()); i++) {
			int cnt = __builtin_popcount(i);

			if (cnt == M) {
				ans = min(ans,  solve(lab, inactivated, i));
			}
		}

		cout << (ans == INF ? -1 : ans);
	}

}