#include <iostream>
using namespace std;

int N, K;
bool visited[100000];

int main(){
    scanf("%d%d", &N, &K);

    int cnt = 1;
    long long tens = 1;

    long long tmp = N % K;

    while (tens <= N){
        tens *= 10;
    }

    while (1){
        if (!(tmp)) {
            printf("%d", cnt);
            break;
        }

        cnt += 1;
        tmp *= tens;
        tmp %= K;
        tmp += N;
        tmp %= K;

        if (visited[tmp]) {
            printf("-1");
            break;
        } 

        visited[tmp] = true;
    }
}