#include <iostream>
#include <string.h>
using namespace std;


int main() {
	char first[1001], second[1001];
	int maxlen = 0;
	scanf(" %s", first);
	scanf(" %s", second);
	int firlen = strlen(first);
	int seclen = strlen(second);
	
	int **dp = new int*[firlen + 1];
	for (int i = 0; i <= firlen; i++) {
		dp[i] = new int[seclen + 1];
	}

	for (int i = 0; i <= firlen; i++) {
		for (int j = 0; j <= seclen; j++) {
			dp[i][j] = 0;
			if (i != 0 && j != 0) {
				if (first[i - 1] == second[j - 1]) { dp[i][j] = dp[i - 1][j - 1] + 1; }
				else dp[i][j] += (dp[i][j - 1] > dp[i - 1][j] ? dp[i][j - 1] : dp[i - 1][j]);
				if (maxlen < dp[i][j]) maxlen = dp[i][j];

			}

		}
	}
	printf("%d", maxlen);

}
