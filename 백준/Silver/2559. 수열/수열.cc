#include <iostream>
using namespace std;

const int MAXN = 100000;
int N, K;
int tempr[MAXN];

int main(){
    scanf("%d%d", &N, &K);
    int sum = 0, ans = -10000000; 
    for (int i = 0; i < N; i++){
        scanf("%d", &tempr[i]);
        if (i < K) sum += tempr[i];
        else {
            sum -= tempr[i - K];
            sum += tempr[i];
        }
        if (i >= K - 1) {
            ans = max(ans, sum);
        }
    }

    printf("%d", ans);
}