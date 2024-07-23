#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

char buffer[51];
int dp[50][50];

int solve(int start, int end) {
	int &ret = dp[start][end];
	if (ret != -1) return ret;
	ret = 0;
	if (start >= end) return ret;

	ret = min({solve(start, end - 1) + 1, solve(start + 1, end) + 1, solve(start + 1, end - 1) + (buffer[start] != buffer[end])});

	return ret;
}

int main(){
	scanf("%s", buffer);
	int len = strlen(buffer);

	memset(dp, -1, sizeof(dp));
	int ans = solve(0, len - 1);

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			memset(dp, -1, sizeof(dp));
			swap(buffer[i], buffer[j]);
			ans = min(ans, solve(0, len - 1) + 1);
			swap(buffer[i], buffer[j]);
		}
	}

	printf("%d", ans);
	
}