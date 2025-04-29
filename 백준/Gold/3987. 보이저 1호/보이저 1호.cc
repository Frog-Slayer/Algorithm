#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int INF = INT_MAX;

int solve(int N, int M, int PR, int PC, vector<string> &v, int dir) {
	bool visited[500][500][4] = { 0, };
	vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

	int ret = 0;
	int x = PR, y = PC, d = dir;

	while (true) {
		ret++;
		x += dx[d], y += dy[d]; 

		if (x < 0 || y < 0 || x >= N || y >= M) return ret;
		if (v[x][y] == 'C') return ret;
		if (visited[x][y][d]) return INF;

		visited[x][y][d] = true;

		if (v[x][y] == '/') {
			if (d == 0 || d == 2) d = (d + 1) % 4;
			else d = (d + 3) % 4;
		}
		else if (v[x][y] == '\\') {
			if (d == 3 || d == 1) d = (d + 1) % 4;
			else d = (d + 3) % 4;
		}

	}

	return ret;
}

int main() {
	fastio;

	int N, M;
	cin >> N >> M;

	vector<string> v(N);

	for (int i = 0; i < N; i++) cin >> v[i];

	int PR, PC;
	cin >> PR >> PC;
	PR--, PC--;

	vector<char> dir = {'U', 'R', 'D', 'L'};

	int ans = 0;
	char d;

	for (int i = 0; i < 4; i++) {
		int tmp = solve(N, M, PR, PC, v, i);

		if (tmp > ans) {
			ans = tmp;
			d = dir[i];
		}
	}

	cout << d << '\n';

	if (ans == INF) cout << "Voyager";
	else cout << ans;

}


