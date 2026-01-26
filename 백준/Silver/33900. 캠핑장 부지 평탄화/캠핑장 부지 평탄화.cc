#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()


int main() { 
	fastio;

	int N, M, R, C;

	cin >> N >> M >> R >> C;

	vector<vector<int>> m(N, vector<int>(M));

	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < M; j++) cin >> m[i][j]; 
	}

	vector<vector<int>> plan(R, vector<int>(C));

	for (int i = 0; i < R; i++) { 
		for (int j = 0; j < C; j++) cin >> plan[i][j];
	}

	int cnt = 0;

	for (int i = 0; i <= N - R; i++) { 
		for (int j = 0; j <= M - C; j++) { 
			int cur = m[i][j] - plan[0][0];
			bool can = true;

			for (int r = 0; r < R; r++) { 
				for (int c = 0; c < C; c++) { 
					if (cur != m[i + r][j + c] - plan[r][c]) { 
						can = false;
						break;
					}
				}
				if (!can) break;
			}

			if (can) cnt++;
		}
	}

	cout << cnt;


}