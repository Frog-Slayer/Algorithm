#include <iostream>
using namespace std;

const int MAXN = 100000;
const int MOD = 9901;
int N;
int arr[MAXN + 1][3];

void solve(){
    arr[0][0] = arr[0][1] = arr[0][2] = 1;
    for (int i = 1; i <= N; i++){
        arr[i][0] = (arr[i-1][0] + arr[i-1][1] + arr[i-1][2]) % MOD;
        arr[i][1] = (arr[i-1][0] + arr[i-1][2]) % MOD;
        arr[i][2] = (arr[i-1][0] + arr[i-1][1]) % MOD;
    }
}

int main(){
    scanf("%d", &N);
    solve();

    printf("%d", arr[N][0]);
}