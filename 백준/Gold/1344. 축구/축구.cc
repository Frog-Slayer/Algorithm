#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	vector<bool> is_prime = {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0};

	double A, B;
	cin >> A >> B;

	A /= 100, B /= 100; 

	double dp[19][19][19] = {0, };
	dp[0][0][0] = 1;

	for (int i = 1; i <= 18; i++) {
		for (int j = 0; j <= i; j++) {
			for (int k = 0; k <= i; k++) {
				if(j) dp[i][j][k] += dp[i - 1][j - 1][k] * A * (1 - B);
				if(k) dp[i][j][k] += dp[i - 1][j][k - 1] * (1 - A) * B;
				if(j && k) dp[i][j][k] += dp[i - 1][j - 1][k - 1] * A * B;
				dp[i][j][k] += dp[i - 1][j][k] * (1 - A) * (1 - B);
			}
		}
	}

	double ans = 0;
	for (int i = 0; i <= 18; i++) {
		for (int j = 0; j <= 18; j++) {
			if (is_prime[i] || is_prime[j]) ans += dp[18][i][j];

		}
	}

	cout << fixed;
	cout.precision(16);

	cout << ans;

}
