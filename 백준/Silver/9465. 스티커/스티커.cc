#include <iostream>
using namespace std;

int T, N, v[2][100000], dp[100001][3];

int max(int a, int b, int c){
    return a > b ? b > c ? a : c : b > c ? b : c;
}

int main(){
    int T;
    scanf("%d", &T);

    while (T--){
        int N;
        scanf("%d", &N);

        for (int i = 0; i < N; i++) {
            dp[i][0] = dp[i][1] = dp[i][2] = 0;
        }

        for (int i = 0; i < N; i++){
            scanf("%d", &v[0][i]);
        }

        for (int i = 0; i < N; i++){
            scanf("%d", &v[1][i]);
        }

        dp[0][1] = v[0][0];
        dp[0][2] = v[1][0];

        for (int i = 1; i < N; i++){
            dp[i][0] = max(dp[i-1][0], dp[i-1][1], dp[i-1][2]);
            dp[i][1] = max(dp[i-1][0], dp[i-1][2]) + v[0][i];
            dp[i][2] = max(dp[i-1][0], dp[i-1][1]) + v[1][i];
        }

        printf("%d\n", max(dp[N-1][0], dp[N-1][1], dp[N-1][2]));
    }


}