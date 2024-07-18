#include <iostream>
using namespace std;

const int MOD = 1000000007;
int M;
int dp[6][7];

int main(){
	scanf("%d", &M);
	M = 6 * M - 15;

	long long ans = 0;

	for (int i = 0; i <= M; i++) {
		int n = i % 6;
		
		for (int k = 1; k <= 6; k++) {
			if (k > i) break;
			if (k == 1 || k == i) dp[n][k] = 1;
			else {
				dp[n][k] = dp[(n + 5) % 6][k - 1] + dp[(n - k + 6) % 6][k];
				dp[n][k] %= MOD;
			}
		}
		ans += dp[n][6];
		ans %= MOD;
	}

	ans *= 30;
	ans %= MOD;

	printf("%lld", ans);

}