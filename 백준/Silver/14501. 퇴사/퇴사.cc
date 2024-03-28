#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 15;
int N, ans;
int t[MAXN], p[MAXN];
int dp[1 << MAXN];

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        scanf("%d%d", &t[i], &p[i]);
    }

    for (int i = 0; i < (1 << N); i++){
        int latest = -1;
        int tmp = 0;

        for (int j = 0; j < N; j++){
            if (i & (1 << j)) {
                if (latest >= j) break;
                if (j + t[j] - 1 >= N) break;
                tmp += p[j];
                latest = max(latest, j + (t[j]) - 1);
            } 

        }
        ans = max(ans, tmp);
    }

    printf("%d", ans);

}