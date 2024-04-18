#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 15;
int N;
char in[MAXN][MAXN + 1];
int dp[MAXN][1 << MAXN];//dp[i][j] 현재 상태가 j일 때, 현재 그림을 들고 있는 사람이 i일 때 살 수 있는 수

int dfs(int cur, int price, int state){
    int newState = state | (1 << cur);
    if (dp[cur][newState]) return dp[cur][newState];

    for (int i = 1; i < N; i++){
        if (in[cur][i] < price) continue;
        if (newState & (1 << i)) continue;

        dp[cur][newState] = max(dp[cur][newState], dfs(i, in[cur][i], newState) + 1);
    }

    return dp[cur][newState];
}

int main(){
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", in[i]);
        for (int j = 0; j < N; j++) in[i][j] -= '0';
    }

    dfs(0, 0, 0);

    printf("%d", dp[0][1] + 1);
}