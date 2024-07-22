#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAX_N = 15;

char buffer[MAX_N + 1];
int seg_count[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5}, N, cnt;
ll num, dp[MAX_N + 1][MAX_N * 7 + 1];
ll tens[MAX_N + 2];

ll solve() {
	ll ans = tens[N] + dp[N][cnt] - num;

	for (int i = 0; i < N; i++) {//i-1번까지는 고정하고, i번째를 바꾼다고 하자.
		ll cur = 0;
		int cur_count = 0;
		for (int j = 0; j < i; j++) {
			cur_count += seg_count[buffer[j] - '0'];
			cur *= 10;
			cur += buffer[j] - '0';
		}

		for (int j = buffer[i] - '0'; j < 10; j++) {//현재 숫자를 j로 바꿨을 때.
			int left = cnt - cur_count - seg_count[j];
			if (left < 0) continue;
			ll next_min = dp[N - i - 1][left];
			ll tmp = (cur * 10 + j) * tens[N - i - 1] + next_min;

			if (i == N - 1 && !left) tmp++;

			if (tmp <= num) continue;

			if (next_min >= 0) ans = min(ans, tmp - num);
			else if (i == N - 1 && !left) ans = min(ans, tmp - num);
		}
	}
	
	return ans;
}

int main() {
	memset(dp, -1, sizeof(dp));

	scanf("%s", buffer);
	N = strlen(buffer);

	for (int i = 0; buffer[i]; i++) cnt += seg_count[buffer[i] - '0'];

	tens[0] = 1;
	for (int i = 1; i <= MAX_N + 1; i++) tens[i] = tens[i - 1] * 10;

	num = atoll(buffer);

	dp[1][2] = 1;
	dp[1][3] = 7;
	dp[1][4] = 4;
	dp[1][5] = 2;
	dp[1][6] = 0;
	dp[1][7] = 8;

	for (int i = 2; i <= N; i++) {
		for (int j = 2; j <= 7; j++) {
			for (int k = 2 * (i - 1); k <= 7 * (i - 1); k++) {
				if (dp[i - 1][k] < 0) continue;
				if (dp[i][j + k] < 0) dp[i][j + k] = tens[MAX_N];
				dp[i][j + k] = min({dp[i][j + k], dp[i - 1][k] + dp[1][j] * tens[i - 1], dp[i - 1][k] * 10 + dp[1][j]});
			}
		}
	}

	printf("%lld\n", solve());
}