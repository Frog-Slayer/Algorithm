#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> v;

int gcd(int a, int b){
    if (!(a * b)) return a + b;
    if (a < b) swap(a, b);
    int r;

    while (b){
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}

int main(){
    scanf("%d", &N);

    v.resize(N);

    int d = 0;

    for (int i = 0; i < N; i++){
        scanf("%d", &v[i]);
        if (i) {
            d = gcd(d, v[i] - v[i-1]);
        }
    }

    int ans = 0;
    for (int i = 1; i < N; i++){
        ans += (v[i] - v[i-1]) / d - 1;
    }

    printf("%d", ans);
}