#include <iostream>
using namespace std;

int main() {
	int N, count = 0;

	scanf("%d", &N);
	int **dp = new int*[N + 1];

	for (int i = 0; i <= N; i++) {
		dp[i] = new int[10]{ 0, };
	}

	for (int i = 1; i < 10; i++) dp[1][i] = 1;

	for (int i = 2; i <= N; i++) {
		for (int j = 0; j < 10; j++) {
			if (j == 0) dp[i][0] = dp[i - 1][1] % 1000000000;
			else if (j == 9) dp[i][9] = dp[i - 1][8] % 1000000000;
			else dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j + 1]) % 1000000000;
		}
	}

	for (int i = 0; i < 10; i++) count = (count + dp[N][i]) % 1000000000;
	
	printf("%d", count);
}