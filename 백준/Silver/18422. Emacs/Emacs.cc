#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()


int main() { 
	fastio;

	int N, M;
	cin >> N >> M;

	vector<string> board(N);
	vector<vector<bool>> visited(N, vector<bool>(M, false));

	for (int i = 0; i < N; i++) cin >> board[i]; 

	int cnt = 0;

	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < M; j++) { 
			if (board[i][j] == '.') continue;
			if (i > 0 && board[i - 1][j] == '*') continue;
			if (j > 0 && board[i][j - 1] == '*') continue;
			if (i > 0 && j > 0 && board[i - 1][j - 1] == '*') continue;
			cnt++;
		}
	}


	cout << cnt;



}
