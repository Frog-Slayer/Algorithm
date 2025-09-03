#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() {
	fastio;

	int R, C;
	cin >> R >> C;

	vector<string> map(R);

	for (int i = 0; i < R; i++) cin >> map[i];

	vector<int> dx = {0, 0, -1, 1}, dy = {1, -1, 0, 0};

	int left = C, bottom = R, right = -1, top = -1;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] == '.') continue;
			int cnt = 0;
			for (int d = 0; d < 4; d++) {
				int nx = i + dx[d], ny = j + dy[d];
				if (nx < 0 || nx >= R || ny < 0 || ny >= C || map[nx][ny] == '.') cnt++;
			}
			
			if (cnt >= 3) map[i][j] = '#';
			else {
				top = max(top, i);
				bottom = min(bottom, i);

				right = max(right, j);
				left = min(left, j);
			}
		}
	}

	for (int i = bottom; i <= top; i++) {
		for (int j = left; j <= right; j++) {
			if (map[i][j] == 'X') cout << 'X';
			else cout << '.';
		}
		cout << '\n';
	}
}
