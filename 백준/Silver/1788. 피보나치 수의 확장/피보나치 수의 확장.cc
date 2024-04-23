#include <iostream>
using namespace std;

const int offset = 1000000;
const int MOD = 1000000000;

int n;
int fibo[1000001 * 2];

int main(){
    scanf("%d", &n);

    fibo[offset] = 0;
    fibo[offset + 1] = 1;

    if (n > 1) {
        for (int i = 2; i <= n; i++){
            fibo[i + offset] = fibo[i + offset - 1] + fibo[i + offset - 2];
            fibo[i + offset] %= MOD; 
        }
    }
    else if (n < 0){
        for (int i = -1; i >= n; i--){
            fibo[i + offset] = fibo[i + offset + 2] - fibo[i + offset + 1];
            fibo[i + offset] %= MOD;
        }
    }

    int ans = fibo[n + offset];
    printf("%d\n", ans < 0 ? -1 : ans ? 1 : 0);
    printf("%d", abs(ans));
}