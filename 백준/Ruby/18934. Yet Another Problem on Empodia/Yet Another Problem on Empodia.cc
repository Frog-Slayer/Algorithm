#include <iostream>
using namespace std;

const int MAXN = 5000;
__int128_t ans[MAXN + 1] = { 0, 1, 1, 3, 12, 52, };
int N, P;

__int128_t mult(__int128_t p, __int128_t q, __int128_t mod){
    p %= mod;
    q %= mod;

    return (p * q) % mod;
}

__int128_t pow_mod(__int128_t a, __int128_t m, __int128_t p){
    __int128_t ret = 1;
    a %= p;

    while (m){
        if (m % 2) ret = mult(ret, a, p);
        a = mult(a, a, p);
        m >>= 1;
    }

    return ret;
}

int main(){
    scanf("%d%d", &N, &P);

    for (__int128_t n = 6; n <= N; n++){
        ans[n] = ((n-1) *(n-2) *(2079652 * n * n - 10492117 * n + 10802220) * ans[n - 1] 
                - 6 * (n - 2) *(98404 * n * n * n -611787 * n * n + 893503 * n +124240) * ans[n - 2] 
                - 2 * (-1206916 * n * n * n * n + 13262653 * n * n * n - 52943063 * n * n + 90096428 * n - 54243072) * ans[n - 3] 
                - (-16564 * n * n * n * n + 1171171 * n * n * n - 12487565 * n * n + 47878166 * n - 62441016) * ans[n - 4]
                - 3 * (3 * n - 14) * (n - 5) * (388 * n - 1861) * (3 * n - 16) * ans[n - 5]);

        __int128_t mod = pow_mod((177 * n * (n-1) * (n-2) * (1884 * n - 6797)), P - 2, P);
        ans[n] = mult(ans[n], mod, P);
        ans[n] += P;
        ans[n] %= P;
    }

    for (int i = 1; i <= N; i++) printf("%d\n", (int)(ans[i]));

}