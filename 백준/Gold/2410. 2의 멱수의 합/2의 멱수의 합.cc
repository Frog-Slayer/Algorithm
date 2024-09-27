#include <iostream>
#include <vector>
using namespace std;
#define fastio cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0)

typedef long long ll;
const int MAX_N = 1e6;
const int MOD = 1e9;

int dp[MAX_N + 1];

int main() {
	int N;
	cin >> N;

	dp[1] = 1;
	for (int i = 2; i <= N; i++) {
		if (i % 2) dp[i] = dp[i - 1];
		else dp[i] = (dp[i - 1] + dp[i / 2]) % MOD;
	}

	cout << dp[N];
}