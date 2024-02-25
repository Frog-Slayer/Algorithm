#include <iostream>
#include <map>
using namespace std;

int N, M, K;
int cnt[50];
char lamp[50][51];
map<long long, int> m;

int main(){
    scanf("%d%d", &N, &M);

    for (int i = 0; i < N; i++){
        scanf("%s", lamp[i]);
        for (int j = 0; j < M; j++){
            cnt[i] += lamp[i][j] == '0';
        }
    }

    scanf("%d", &K);


    for (int i = 0; i < N; i++){
        if (cnt[i] > K) continue;
        if (cnt[i] % 2 != K % 2) continue;

        long long flag = 0;
        for (int j = 0; j < M; j++){
            if (lamp[i][j] == '0') flag |= (1LL << j);
        }

        m[flag]++;
    }

    int ans = 0;
    for (pair<long long, int> p : m){
        ans = max(ans, p.second);
    }

    printf("%d", ans);

}