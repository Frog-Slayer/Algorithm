#include <iostream>
#include <string.h>
using namespace std;

const int MAX_NM = 300;
const int MAX_WORD_LENGTH = 50;
const int MOD = 1000000007;
int N, M, L;
int word_length;

char board[MAX_NM][MAX_NM + 1];
char word[MAX_WORD_LENGTH + 1];
int dp[MAX_WORD_LENGTH][MAX_NM][MAX_NM];

int sum(int idx, int bottom, int right, int top, int left) {
	bottom = min(bottom, N - 1);
	right = min(right, M - 1);

	left = max(left, - 1);
	top = max(top, - 1);

	if (left >= right || bottom <= top) return 0;

	int ret = dp[idx][bottom][right];

	if (left >= 0) ret -= dp[idx][bottom][left];
	if (top >= 0) ret -= dp[idx][top][right];
	if (left >= 0 && top >= 0) ret += dp[idx][top][left];

	ret %= MOD;
	if (ret < 0) ret += MOD;

	return ret;
}

int count(int idx, int row, int col) {
	int ret = dp[idx][N - 1][M - 1];

	ret -= sum(idx, row - 3, col + 1, -1, col - 2);
	ret %= MOD;

	ret -= sum(idx, row + 1, col - 3, row - 2, -1);
	ret %= MOD;

	ret -= sum(idx, row + 1, M - 1, row - 2, col + 2);
	ret %= MOD;

	ret -= sum(idx, N - 1, col + 1, row + 2, col - 2);
	ret %= MOD;

	ret -= sum(idx, row + 2, col + 2, row - 3, col - 3);
	ret %= MOD;

	if (ret < 0) ret += MOD;

	return ret;
}

void solve(int idx) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == word[idx]) {
				if (!idx) dp[idx][i][j] = 1;
				else dp[idx][i][j] = count(idx - 1, i, j);
			}

			dp[idx][i][j] += i ? dp[idx][i - 1][j] : 0;
			dp[idx][i][j] %= MOD;

			dp[idx][i][j] += j ? dp[idx][i][j - 1] : 0;
			dp[idx][i][j] %= MOD;

			dp[idx][i][j] -= (i && j) ? dp[idx][i - 1][j - 1] : 0;
			dp[idx][i][j] %= MOD;

			if (dp[idx][i][j] < 0) dp[idx][i][j] += MOD;
		}
	}
}

int main(){

	scanf("%d%d%d", &N, &M, &L);

	scanf("%s", word);
	int word_length = strlen(word);

	for (int i = 0; i < N; i++) {
		scanf("%s", board[i]);
	}

	for (int i = 0; i < word_length; i++) solve(i);

	printf("%d", dp[word_length - 1][N - 1][M - 1]);
}