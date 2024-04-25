#include <iostream>
using namespace std;

const int MAXN = 50000;
int mobi[MAXN + 1];

void setMobi(){
    mobi[1] = 1;
    for (int i = 1; i <= MAXN; i++){
        for (int j = 2 * i; j <= MAXN; j += i){
            mobi[j] -= mobi[i];
        }
        mobi[i] += mobi[i - 1];
    }
}

int main(){
    int N;
    scanf("%d", &N);
    setMobi();

    while (N--){
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        if (a > b) swap(a, b);
        a /= d;
        b /= d;

        int ans = 0;
        for (int i = 1, j; i <= a; i = j + 1){
            j = a / (a / i);
            for (int k = i, l; k <= j; k = l + 1){
                l = min(b / (b / k), j);
                ans += (mobi[l] - mobi[k - 1]) * (a / k) * (b / k);
            }
        }

        printf("%d\n", ans);
    }

}