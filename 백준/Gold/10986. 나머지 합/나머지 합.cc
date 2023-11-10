#include <iostream>
using namespace std;

int N, M;
long long A[1000001];
long long accSum[1000001];
long long cnt[1001];

int main(){
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; i++){
        scanf("%lld", &A[i]);
        accSum[i] = (accSum[i - 1] + A[i]) % M; 
        cnt[accSum[i]]++;
    }
    
    long long ans = 0;
    for (int i = 0; i < M; i++){
        if (!i) ans += cnt[i];

        if (cnt[i]) {
            ans += cnt[i] * (cnt[i] - 1) / 2;
        }
    }

    printf("%lld", ans);
}