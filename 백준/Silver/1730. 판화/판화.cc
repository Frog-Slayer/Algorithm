#include <iostream>
#include <unordered_set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;
	int mok[10][10] = {0,};
	char v[4] = {'.', '-', '|', '+'};

	int N;
	cin >> N;

	string move;
	cin >> move;

	int x = 0, y = 0;

	for (char c: move) {
		int nx = x, ny = y;

		if (c == 'U') nx--;
		else if (c == 'D') nx++;

		if (c == 'L') ny--;
		else if (c == 'R') ny++;


		if (c == 'U' || c == 'D') {
			if (nx < 0) nx = 0;
			else if (nx >= N) nx = N - 1;
			else {
				mok[x][y] |= 2;
				mok[nx][ny] |= 2;
			}
		}
		else {
			if (ny < 0) ny = 0;
			else if (ny >= N) ny = N - 1;
			else {
				mok[x][y] |= 1;
				mok[nx][ny] |= 1;
			}
		}

		x = nx, y = ny;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << v[mok[i][j]];
		}
		cout << '\n';
	}
}
