#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()


int main() { 
	fastio;

	int N, a, b;
    cin >> N >> a >> b;

	vector<int> dp(N + 1, N + 1);
	dp[N] = 0;

	for (int i = N; i >= 0; i--) { 
		if (i - 1 >= 0) dp[i - 1] = min(dp[i - 1], dp[i] + 1);
		if (i - a - 1 >= 0) dp[i - a - 1] = min(dp[i - a - 1], dp[i] +1);
		if (i - b - 1 >= 0) dp[i - b - 1] = min(dp[i - b - 1], dp[i] +1);
	}

	cout << dp[0];

}
