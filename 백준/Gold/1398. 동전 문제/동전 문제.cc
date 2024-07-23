#include <iostream>
#include <vector>
using namespace std;

typedef long long ll; int T; ll N;
int coins[3] = {1, 10, 25};
int dp[100];

int main(){
	scanf("%d", &T);

	for (int i = 1; i < 100; i++) {
		dp[i] = i;
	
		for (int j = 0; j < 3; j++) {
			if (i >= coins[j]) dp[i] = min(dp[i - coins[j]] + 1, dp[i]);
		}
	}

	for (int i = 0; i < T; i++) {
		scanf("%lld", &N);

		int ans = 0;
		while (N) {
			int tmp = N % 100;
			ans += dp[tmp];
			N /= 100;
		}

		printf("%d\n", ans);
	}
}