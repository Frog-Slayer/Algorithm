#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 100;
int N, M, cnt, sum;
vector<pair<int, int>> items;
int dp[10001][14 * MAX_N + 1];

int main() {
	scanf("%d%d", &N, &M);
	items.emplace_back(0, 0);

	for (int i = 0; i < N; i++) {
		int v, c, k;
		scanf("%d%d%d", &v, &c, &k);

		sum += v;

		for (int j = k; j; j >>= 1) {
			int tmp = j - (j / 2);
			items.emplace_back(v * tmp, c * tmp);
		}
	}

	for (int i = 1; i <= M; i++) {
		for (int j = 1; j < items.size(); j++) {
			dp[i][j] = dp[i][j - 1];
			if (i - items[j].first < 0) continue;
			dp[i][j] = max(dp[i][j], dp[i - items[j].first][j - 1] + items[j].second);
		}
	}

	printf("%d", dp[M][items.size() - 1]);




}