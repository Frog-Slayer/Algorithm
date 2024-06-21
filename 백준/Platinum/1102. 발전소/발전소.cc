#include <iostream>
using namespace std;

const int MAX_N = 16;
const int INF = 999;
int N, P;
int power_plant[MAX_N][MAX_N];
int dp[1 << MAX_N];
char is_on[MAX_N + 1];

int dfs(int flag, int cnt) {
	if (cnt >= P) return 0; 
	if (dp[flag] != INF) return dp[flag];

	for (int i = 0; i < N; i++) {
		if (!(flag & (1 << i))) continue;
		for (int j = 0; j < N; j++) {
			if (flag & (1 << j)) continue; 
			int next_flag = flag | (1 << j);
			dp[flag] = min(dp[flag], dfs(next_flag, cnt + 1) + power_plant[i][j]);
		}
	}

	return dp[flag];
}

int main(){
	scanf("%d", &N);
	
	for (int i = 0; i < (1 << MAX_N); i++) {
		dp[i] = 999;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &power_plant[i][j]);
		}
	}

	scanf("%s", is_on);
	scanf("%d", &P);

	int flag = 0;
	int cnt = 0;

	for (int i = 0; i < N; i++) {
		if (is_on[i] == 'Y') {
			flag |= (1 << i);
			cnt++;
		}
	}
	
	int ans = dfs(flag, cnt);

	printf("%d", ans == INF ? -1 : ans);

}