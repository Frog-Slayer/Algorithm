#include <iostream>
using namespace std;

const int MAXN = 1000;
int N, M;
char arr[MAXN][MAXN + 1];
int dp[MAXN][MAXN];

int min(int a, int b, int c) {
    return a < b ? a < c ? a : c : b < c ? b : c;
}

int main(){
    scanf("%d%d", &N, &M);

    for (int i = 0; i < N; i++){
        scanf("%s", arr[i]);
    }

    int ans = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (arr[i][j] == '0') continue;
            dp[i][j] = min(i ? dp[i-1][j] : 0, j ? dp[i][j-1] : 0, (i && j) ? dp[i-1][j-1] : 0) + 1;
            ans = max(ans, dp[i][j]);
        }
    }
    
    printf("%d", ans * ans);
}
