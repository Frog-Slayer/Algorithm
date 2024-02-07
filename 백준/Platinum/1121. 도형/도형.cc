#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50;
const int MAXK = 10;
const int INF = 50001;

int N, K;
int segLen[MAXN];
int dp[MAXN][MAXK + 1][INF + 1];

int main(){
	scanf("%d", &N);

	for (int i = 0; i < N; i++){
		scanf("%d", &segLen[i]);
	}

	scanf("%d", &K);

	if (N < 3) {
		printf("0");
		return 0;
	}

	sort(segLen, segLen + N);

	dp[0][1][segLen[0]] = 1;

	for (int i = 1; i < N; i++){
		dp[i][1][segLen[i]]++;
		for (int j = 1; j <= K; j++){
			for (int k = 0; k <= INF; k++){
				dp[i][j][k] += dp[i-1][j][k];//i번째 안 쓰고 합이 k개임 = i-1번째까지 j개 뽑아서 합이 k인 경우
				int tmp = k + segLen[i];
				if (tmp >= INF) tmp = INF;
				dp[i][j][tmp] += dp[i - 1][j - 1][k]; 
			}
		}
	}

	long long ans = 0;

	for (int i = 1; i < N; i++){//i번째가 제일 큰 경우
		for (int j = segLen[i] + 1; j <= INF; j++){//i-1번째까지 K-1개를 뽑았을 때의 합이 i번의 길이보다 커야 함
			ans += dp[i - 1][K - 1][j];
		}
	}
	printf("%lld", ans);

}