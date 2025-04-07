#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

const int MAX_N = 50;
int N, M;
vector<int> dx = {0, -1, -1, -1, 0, 1, 1, 1};
vector<int> dy = {-1, -1, 0, 1, 1, 1, 0, -1};
int r[MAX_N][MAX_N], version[MAX_N][MAX_N];

pair<int, int> move(int x, int y, int d, int s) {
	int nx = x + dx[d] * s, ny = y + dy[d] * s;

	nx %= N, ny %= N;
	nx += N, ny += N;
	nx %= N, ny %= N;
	
	return {nx, ny};
}

void rain(int x, int y, int v) {
	r[x][y]++;
	version[x][y] = v;
}

int bug(int x, int y) {
	int ret = 0;

	for (int d = 1; d < 8; d += 2) {
		int nx = x + dx[d], ny = y + dy[d];
		if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
		if (r[nx][ny]) ret++;
	}

	return ret;
}

int main() {
	fastio;

	cin >> N >> M;

	queue<pair<int, int>> clouds;
	queue<tuple<int, int, int>> bug_q;

	clouds.emplace(N - 1, 0);
	clouds.emplace(N - 1, 1);
	clouds.emplace(N - 2, 0);
	clouds.emplace(N - 2, 1);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) cin >> r[i][j];
	}

	for (int i = 1; i <= M; i++) {
		int d, s;
		cin >> d >> s;
		d--;

		//구름 이동 + 비내리기
		while (!clouds.empty()) {
			auto [x, y] = clouds.front();
			clouds.pop();
			auto [nx, ny] = move(x, y, d, s);
			rain(nx, ny, i);
		}

		//물복사 버그
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				if (version[j][k] == i) bug_q.emplace(j, k, bug(j, k));
			}
		}

		while (!bug_q.empty()) {
			auto [x, y, amt] = bug_q.front();
			bug_q.pop();
			r[x][y] += amt;
		}

		//새 구름
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				if (r[j][k] >= 2 && version[j][k] != i) {
					r[j][k] -= 2;
					clouds.emplace(j, k);
				}
			}
		}
	}

	int ans = 0;

	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) ans += r[i][j];

	cout << ans;
			
}
