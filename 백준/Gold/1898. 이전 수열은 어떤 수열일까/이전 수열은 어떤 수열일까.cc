#include <iostream>
using namespace std;

const int MAXN = 50000;

int N, reserve[MAXN + 1];
bool isInUse[MAXN + 1];

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        int n;
        scanf("%d", &n);
        //이것보다 1 작은 거 넣을 수 있음? (이미 들어갔나? or 예약됨?) 
        //만약 못 넣으면 다음 거 가능?
        if (reserve[n]) {
            printf("%d\n", reserve[n]);
            isInUse[n] = true;
        }
        else if (!isInUse[n-1] && n > 1){
            isInUse[n - 1] = true;
            isInUse[n] = true;
            reserve[n - 1] = n;
            printf("%d\n", n - 1);
        }
        else {
            reserve[n] = n;
            isInUse[n] = true;
            printf("%d\n", n);
        }
    }
}