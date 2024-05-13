#include <iostream>
using namespace std;

const int MAXN = 300000;
int N;
int triangle[777];
int dp[MAXN + 1];

int main(){
	scanf("%d", &N);

	for (int i = 1; i < 777; i++){
		triangle[i] = triangle[i-1] + i;
	}

	int t = 0;
	for (t = 1; ; t++){
		triangle[t] += triangle[t - 1]; 
		if (triangle[t] > N) break;
		dp[triangle[t]] = 1;
	}

	for (int i = 1; i <= N; i++){
		if (!dp[i]) dp[i] = i;

		for (int j = 0; j < t; j++){
			if (i - triangle[j] < 0) continue;
			dp[i] = min(dp[i], dp[i - triangle[j]] + 1);
		}
	}

	printf("%d", dp[N]);

}