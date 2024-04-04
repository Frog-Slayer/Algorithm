#include <iostream>
using namespace std;

const int MOD = 1000000000;

int N;
int dp[101][10][(1 << 10)];

int main(){
    scanf("%d", &N);

    for (int i = 1; i < 10; i++){
        dp[1][i][1 << i] = 1;
    }

    for (int i = 2; i <= N; i++){
        for (int j = 0; j < 10; j++){
            if (j > 0){
                for (int k = 0; k < (1 << 10); k++){
                    dp[i][j][(k | (1 << j))] += dp[i - 1][j - 1][k];
                    dp[i][j][(k | (1 << j))] %= MOD;
                }
            }

            if (j < 9){
                for (int k = 0; k < (1 << 10); k++){
                    dp[i][j][(k | (1 << j))] += dp[i - 1][j + 1][k];
                    dp[i][j][(k | (1 << j))] %= MOD;
                }
            }
        }
    }

    int ans = 0;

    for (int i = 0; i < 10; i++){
        ans += dp[N][i][(1 << 10) - 1];
        ans %= MOD;
    }

    printf("%d", ans);

}