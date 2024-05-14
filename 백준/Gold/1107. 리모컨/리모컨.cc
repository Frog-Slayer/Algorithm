#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 500000;
int N, M;
vector<int> pressable;
bool isBroken[10];

int press(int cnt, int num){
    if (num >= MAXN * 2) return MAXN;
    
    int ret = cnt? cnt + abs(N - num) :MAXN;

    for (int i = 0; i < pressable.size(); i++){
        int button = pressable[i];
        if (num == 0 && cnt >= 1 && button == 0) continue;
        ret = min(press(cnt + 1, num * 10 + button), ret);
    }

    return ret;
}

int main(){
    scanf("%d", &N);
    scanf("%d", &M);

    for (int i = 0; i < M; i++){
        int b;
        scanf("%d", &b);
        isBroken[b] = true;
    }

    if (N == 100) {
        printf("0");
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (!isBroken[i]) pressable.push_back(i);
    }

    int ans = min(press(0, 0), abs(N - 100));

    printf("%d", ans);
}