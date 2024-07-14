#include <iostream>
using namespace std;

const int MOD = 9901;
const int MAX_N = 14;
int N, M;
int dp[MAX_N * MAX_N][1 << MAX_N];

int solve(int i, int flag){
	int row = i / M, col = i % M;
	if (row >= N) return (i == N * M && !flag);

	int &ret = dp[i][flag];
	if (ret >= 0) return ret;
	ret = 0;

	if (flag & 1) ret += solve(i + 1, flag >> 1);
	else {
		if (col < M - 1 && !(flag & 2)) ret += solve(i + 2, flag >> 2); 
		ret += solve(i + 1, (flag >> 1) | (1 << (M - 1)));
	}
	ret %= MOD;

	return ret;
}

int main(){
	scanf("%d%d", &N, &M);

	for (int i = 0; i < N * M; i++) for (int j = 0; j < (1 << M); j++) dp[i][j] = -1;
	printf("%d", solve(0, 0));
}