#include <iostream>
#include <memory.h>
using namespace std;

const int MOD = 1000000007;
const int MAX_N = 1000;
int N, A;
int dp[MAX_N][10][11][10];

int solve(int idx, int cnt, int prev_dist, int prev_num){
	if (idx == N - 1) return cnt == A;

	int &ret = dp[idx][cnt][prev_dist][prev_num];
	if (ret != -1) return ret;
	ret = 0;

	if (prev_dist == 10) {//새로 시작
		for (int i = prev_num; i < 10; i++) {
			ret += solve(idx + 1, cnt, i - prev_num, i); 
			ret %= MOD;
		}
	}
	else {//이전 거 이어서 가볼까?
		for (int i = prev_num; i < 10; i++) {
			if (i == prev_num + prev_dist) ret += solve(idx + 1, cnt, prev_dist, i);
			else ret += solve(idx + 1, cnt + 1, 10, i);
			ret %= MOD;
		}
	}
	return ret;
}

int main() {
	memset(dp, -1, sizeof(dp));

	scanf("%d%d", &N, &A);

	if (A > 9) {
		printf("0");
		return 0;
	}

	int ans = 0;
	for (int i = 1; i < 10; i++) {
		ans += solve(0, 1, 10, i);
		ans %= MOD;
	}
	printf("%d", ans);
}