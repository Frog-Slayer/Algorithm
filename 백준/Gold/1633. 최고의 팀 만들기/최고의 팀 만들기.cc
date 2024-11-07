#include <iostream>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	int dp[16][16] = {0, };
	int i = 0, ans = 0;
	int white, black;

	while (cin >> white >> black) {
		if (!i) {
			dp[1][0] = white;
			dp[0][1] = black;
		}
		else {
			for (int w = 15; w >= 0; w--) {
				for (int b = 15; b >= 0; b--) {
					int tmp1 = 0, tmp2 = 0;
					if (w) tmp1 = dp[w - 1][b] + white;
					if (b) tmp2 = dp[w][b - 1] + black;

					dp[w][b] = max({dp[w][b], tmp1, tmp2});

					ans = max(ans, dp[w][b]);
				}
			}
		}

		i++;
	}

	cout << ans;
}