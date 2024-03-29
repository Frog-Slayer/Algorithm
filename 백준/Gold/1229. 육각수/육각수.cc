#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1000000;
int N;
vector<int> hexa;
int dp[MAXN + 1];


int main(){
    scanf("%d", &N);

    hexa.push_back(1);
    dp[1] = 1;
    int tmp = 5;

    while (true){
        int n = hexa.back() + tmp;
        if (n > N) break;
        hexa.push_back(n);
        dp[n] = 1;
        tmp += 4;

    }


    for (int i = 1; i <= N; i++){
        if (dp[i]) continue;
        dp[i] = 6;
        for (int j = 0; j < hexa.size(); j++){
            if (i < hexa[j]) break;
            dp[i] = min(dp[i], dp[i - hexa[j]] + 1);
        }
    }


    printf("%d", dp[N]);
}