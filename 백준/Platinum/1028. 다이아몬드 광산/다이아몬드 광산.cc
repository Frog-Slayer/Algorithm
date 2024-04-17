#include <iostream>
using namespace std;

const int MAXRC = 750;
const int LEFT = 0, RIGHT = 1;

int R, C;
int dp[MAXRC][MAXRC + 1][2];
char dia[MAXRC][MAXRC + 1];

int main(){
    scanf("%d%d", &R, &C);

    for (int i = 0; i < R; i++) scanf("%s", dia[i]);

    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            if (dia[i][j] == '0') continue;

            dp[i][j][LEFT]++;
            dp[i][j][RIGHT]++;

            if (!i) continue;

            if (j){//왼쪽에서 내려오는 경우
                dp[i][j][LEFT] += dp[i - 1][j - 1][LEFT];
            }

            if (j != C - 1) {//오른쪽 위에서 내려오는 경우 
                dp[i][j][RIGHT] += dp[i - 1][j + 1][RIGHT];
            }
        }
    }
    
    int ans = 0;
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            int minLength = min(dp[i][j][LEFT], dp[i][j][RIGHT]);
            for (int l = 0; l < minLength; l++){
                if (dp[i - l][j - l][RIGHT] >= l + 1 && dp[i - l][j + l][LEFT] >= l + 1) ans = max(ans, l + 1);
            }
        }
    }

    printf("%d", ans);
}