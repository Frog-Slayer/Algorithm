#include <iostream>
#include <vector>
using namespace std;

const int MOD = 10000003;
const int MAXS = 100000;
int N;
long long dp[50][MAXS + 1];
vector<int> S;

int gcd(int a, int b){
    if (!(a | b)) return 0;
    if (a < b) swap(a, b);
    int r;

    while (b){
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        int n;
        scanf("%d", &n);
        S.push_back(n);
    }

    dp[0][S[0]]++;

    for (int i = 1; i < N; i++){
        dp[i][S[i]]++;
        for (int j = 1; j <= MAXS; j++){//i번쨰 미포함
            dp[i][j] += dp[i-1][j];
            int g = gcd(j, S[i]);
            dp[i][g] += dp[i-1][j];
            dp[i][j] %= MOD;
            dp[i][g] %= MOD;
        }
    }

    printf("%lld", dp[N - 1][1]);
}