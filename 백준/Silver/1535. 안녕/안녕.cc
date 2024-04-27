#include <iostream>
using namespace std;

const int MAXN = 20;
int N;
int gain[MAXN], lose[MAXN];
int dp[MAXN][101];//dp[i][j]: 지금 i번째 사람을 보고 있고, 체력이 j일 때 얻을 수 있는 최대 기쁨

int main(){
    scanf("%d", &N);
    for (int i = 0; i < N; i++){
        scanf("%d", &lose[i]);
    }

    for (int i = 0; i < N; i++){
        scanf("%d", &gain[i]);
    }

    dp[0][100] = 0;
    if (lose[0] < 100) dp[0][100 - lose[0]] = gain[0];

    for (int i = 1; i < N; i++){

        for (int j = 0; j <= 100; j++){
            //i번째 사람을 선택한 경우
            if (j > lose[i]) {
                dp[i][j - lose[i]] = max(dp[i][j - lose[i]], dp[i - 1][j] + gain[i]);
            }

            //선택하지 않은 경우
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
    }


    int ans = 0;
    for (int i = 1; i <= 100; i++) ans = max(ans, dp[N - 1][i]);
    printf("%d", ans);
}