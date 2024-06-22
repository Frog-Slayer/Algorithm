#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 16;
int N, K;
long long dp[1 << MAX_N][MAX_N];
vector<int> height;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> K;
	height.resize(N);

	for (int i = 0; i < N; i++){
		cin >> height[i];
		dp[(1 << i)][i] = 1;
	}

	for (int flag = 0; flag < (1 << N); flag++) {
		for (int i = 0; i < N; i++) {
			if (!(flag & (1 << i))) continue;
			for (int j = 0; j < N; j++) {
				if (flag & (1 << j)) continue;
				if (abs(height[i] - height[j]) > K) {
					dp[flag | (1 << j)][j] += dp[flag][i];
				}
			}
		}
	}

	long long ans = 0;

	for (int i = 0; i < N; i++) {
		ans += dp[(1 << N) - 1][i];
	}

	cout << ans;
}