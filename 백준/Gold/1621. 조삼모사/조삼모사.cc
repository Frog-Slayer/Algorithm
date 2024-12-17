#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int INF = 2e9;

int main() {
	fastio;

	int N;
	cin >> N;

	int K, C;
	cin >> K >> C;

	vector<int> dp(N + 1, INF), weights(N + 1);
	dp[0] = 0, weights[0] = 0;

	for (int i = 1; i <= N; i++) cin >> weights[i];

	vector<bool> bt(N + 1);

	for (int i = 1; i <= N; i++) {
		if (i >= K && dp[i - 1] + weights[i] > dp[i - K] + C) {
			dp[i] = dp[i - K] + C;
			bt[i] = true;
		}
		else dp[i] = dp[i - 1] + weights[i];
	}

	cout << dp[N] << '\n';

	int cur = N;
	vector<int> v;

	while (cur != 0) {
		if (bt[cur]){
			cur = cur - K;
			v.emplace_back(cur + 1);
		}
		else cur = cur - 1;
	}

	cout << v.size() << '\n';

	for (int i = v.size() - 1; i >= 0; i--) cout << v[i] << '\n';
}