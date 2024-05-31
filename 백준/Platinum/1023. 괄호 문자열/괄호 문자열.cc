#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAX_N = 50;

int N;
ll K;

ll dp[MAX_N + 1][MAX_N + 1];//dp[i][j] = 앞에 (가 연속으로 i개 있고, 뒤에 남은 게 j개일 때의 괄호 ㄴㄴ문자열의 개수

int main(){
    scanf("%d%lld", &N, &K);
    K++;

    for (int i = 1; i <= N; i++) dp[i][0] = 1;

    for (int i = 1; i <= N; i++){
        dp[0][i] = dp[1][i - 1] + (1LL << (i - 1));//전체 = ( 하나 있는 경우, 길이 i일 때 + )로 시작하는 경우

        for (int j = 1; j <= N - i; j++) dp[j][i] = dp[j - 1][i - 1] + dp[j + 1][i - 1];
    }

    if (dp[0][N] < K) printf("-1");
    else {
        bool noBracketString = (N % 2);
        int openBracketCount = 0;

        for (int i = 0; i < N; i++){
            if (noBracketString){
                if (K > (1LL << (N - i- 1))) {
                    printf(")");
                    K -= (1LL << (N - i - 1));
                }
                else printf("(");
            }
            else {
                if (K > dp[openBracketCount + 1][N - i - 1]){
                    K -= dp[openBracketCount + 1][N - i - 1];
                    openBracketCount--;
                    printf(")");
                }
                else {
                    printf("(");
                    openBracketCount++;
                }
            }

            if (openBracketCount < 0) noBracketString = true;
        }
    }
}