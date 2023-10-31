#include <iostream>
using namespace std;

int N, M;
char rect[50][51];
int cumSum[50][50];

int main(){
    scanf("%d%d", &N, &M);

    for (int i = 0; i < N; i++) {
        scanf("%s", rect[i]);
        for (int j = 0; j < M; j++) {
            rect[i][j] -= '0';
            long long up = i ? cumSum[i - 1][j] : 0; 
            long long left = j ? cumSum[i][j-1] : 0;
            long long upLeft = (i && j) ? cumSum[i-1][j-1] : 0;

            cumSum[i][j] = up + left - upLeft + rect[i][j]; 
        }
    }

    //이거 기준으로 좌-우상우하, 상-좌하우하, 하-좌상우상, 우-좌상좌하 
    long long ans = 0;
    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < M; j++){
            long long left = cumSum[N - 1][i]; 
            long long mid = cumSum[N - 1][j]  - cumSum[N - 1][i]; 
            long long right = cumSum[N - 1][M - 1] - cumSum[N - 1][j]; 

            ans = max(ans, left * mid * right);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++){
            long long top = cumSum[i][M - 1]; 
            long long mid = cumSum[j][M - 1]  - cumSum[i][M - 1]; 
            long long bot = cumSum[N - 1][M - 1] - cumSum[j][M - 1]; 

            ans = max(ans, top * mid * bot);
        }
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            long long upLeft = cumSum[i][j];
            long long upRight = cumSum[i][M - 1] - cumSum[i][j];

            long long downLeft = cumSum[N - 1][j] - cumSum[i][j];
            long long downRight = cumSum[N - 1][M - 1] - cumSum[N - 1][j] - cumSum[i][M - 1] + cumSum[i][j];

            ans = max(ans, (upLeft + upRight) * downLeft * downRight);
            ans = max(ans, (upLeft + downLeft) *  upRight* downRight);
            ans = max(ans, (downLeft + downRight) * upLeft * upRight);
            ans = max(ans, (upRight + downRight) * upLeft * downLeft);
        }
    }

    printf("%lld", ans);
}