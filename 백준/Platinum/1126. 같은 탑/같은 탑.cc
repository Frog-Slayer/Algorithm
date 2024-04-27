#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 50;
const int MAX_HEIGHT = 500000;
int N;
int dp[MAXN][MAX_HEIGHT + 1];
vector<int> height;

int main(){
    scanf("%d", &N);
    height.resize(N);

    for (int i = 0; i < N; i++){
        scanf("%d", &height[i]);
    }

    dp[0][height[0]] = height[0];

    for (int i = 1; i < N; i++){
        dp[i][height[i]] = height[i];
        for (int j = 0; j <= MAX_HEIGHT / 2; j++){
            if (!dp[i - 1][j]) continue;
            //작은 거에 더하는 경우
            if (height[i] > j) dp[i][height[i] - j] = max(dp[i][height[i] - j], dp[i - 1][j] - j + height[i]);//더했을 때 그 높이가 원래 컸던 것보다 커지는 경우
            else dp[i][j - height[i]] = max(dp[i][j - height[i]], dp[i -1][j]); //작은 거에 더해도 그 높이가 원래 컸던 것보다 작은 경우

            //큰 거에 더해주기 
            dp[i][j + height[i]] = max(dp[i][j + height[i]], dp[i - 1][j] + height[i]);
            //안 넣을래
            dp[i][j] = max(dp[i][j], dp[i-1][j]);
        }
    }

    if (dp[N-1][0]) printf("%d", dp[N-1][0]);
    else printf("-1");
}