#include <iostream>
using namespace std;

const int MAXN = 10000;
const int BOTH = 0, OUTER = 1, INNER = 2;
const int INF = MAXN * 2;

int N, W;
int inner[MAXN], outer[MAXN];
int dp[MAXN][3];

void fill(int start, int end, int init){
    for (int i = start; i < end; i++){
        dp[i][OUTER] = min(dp[i-1][BOTH] + 1, dp[i-1][INNER] + (outer[i-1] + outer[i] <= W ? 1 : 2));
        dp[i][INNER] = min(dp[i-1][BOTH] + 1, dp[i-1][OUTER] + (inner[i-1] + inner[i] <= W ? 1 : 2));

        dp[i][BOTH] = dp[i-1][BOTH] + (outer[i] + inner[i] <= W ? 1 : 2);
        dp[i][BOTH] = min(dp[i][BOTH], (i > 1 ? dp[i-2][BOTH] : init) + (outer[i-1] + outer[i] <= W ? 1 : 2) + (inner[i-1] + inner[i] <= W ? 1 : 2));
        dp[i][BOTH] = min(dp[i][BOTH], dp[i-1][OUTER] + (inner[i] + inner[i-1] <= W ? 1 : 2) + 1);
        dp[i][BOTH] = min(dp[i][BOTH], dp[i-1][INNER] + (outer[i] + outer[i-1] <= W ? 1 : 2) + 1);
    }
}

void log(){
    printf("OUTER: ");
    for (int i = 0; i < N; i++) printf("%d ", dp[i][OUTER]);
    printf("INNER: ");
    for (int i = 0; i < N; i++) printf("%d ", dp[i][INNER]);
    printf("BOTH: ");
    for (int i = 0; i < N; i++) printf("%d ", dp[i][BOTH]);
}

int main(){
    int T;
    scanf("%d", &T);
    while (T--){
        scanf("%d%d", &N, &W);
        int ans = INF;
        for (int i = 0; i < N; i++) scanf("%d", &inner[i]);
        for (int i = 0; i < N; i++) scanf("%d", &outer[i]);

        if (N == 1){
            ans = (inner[0] + outer[0] <= W ? 1 : 2);
            printf("%d\n", ans);
            continue;
        }

        dp[0][OUTER] = 1;
        dp[0][INNER] = 1;
        dp[0][BOTH] = (inner[0] + outer[0] <= W ? 1 : 2); 
        fill(1, N, 0);
        ans = min(ans, dp[N-1][BOTH]);

        if (inner[0] + inner[N-1] <= W){//안쪽
            dp[0][INNER] = 1;
            dp[0][OUTER] = INF; 
            dp[0][BOTH] = 2; 
            fill(1, N, INF);
            ans = min(ans, dp[N-1][OUTER]);
        }

        if (outer[0] + outer[N-1] <= W){//바깥쪽
            dp[0][INNER] = INF;
            dp[0][OUTER] = 1; 
            dp[0][BOTH] = 2;
            fill(1, N, INF);
            ans = min(ans, dp[N-1][INNER]);
        }

        if (outer[0] + outer[N-1] <= W && inner[0] + inner[N-1] <= W) {//양쪽
            dp[0][INNER] = INF;
            dp[0][OUTER] = INF;
            dp[0][BOTH] = 2;
            fill(1, N - 1, INF);
            ans = min(ans, dp[N-2][BOTH]);
        }

        printf("%d\n", ans);
    }
}