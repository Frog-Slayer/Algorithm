#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N;
	cin >> N;

	vector<int> A(N);
	vector<vector<int>> dp(N, vector<int>(2));

	for (int i = 0; i < N; i++){
		cin >> A[i];
		dp[i][0] = dp[i][1] = A[i];
	}
	
	int ans = A[0];

	for (int i = 1; i < N; i++) {
		dp[i][0] = max(dp[i - 1][0] + A[i], dp[i][0]);
		dp[i][1] = max(dp[i - 1][0], dp[i - 1][1] + A[i]);

		ans = max({ans, dp[i][0], dp[i][1]});
	}

	cout << ans;

}