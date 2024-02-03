#include <iostream>
#include <vector>
using namespace std;

vector<int> D, M;
bool isNotPrime[31624];

int gcd(int a, int b){
    int r;
    if (a < b) swap(a, b);

    while (b){
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main(){
    int d, m;
    scanf("%d%d", &d, &m);

    D.resize(d);
    M.resize(m);

    long long lcm = 1;

    for (int i = 0; i < d; i++){
        scanf("%d", &D[i]);
        lcm = (lcm * D[i] / gcd(lcm, D[i]));
    }

    int g = M[0];

    for (int i = 0; i < m; i++){
        scanf("%d", &M[i]);
        g = gcd(g, M[i]);
    }

    for (int i = 2; i * i <= g; i++){
        if (isNotPrime[i]) continue;

        for (int j = 2 * i; j <= 31624; j+= i) {
            isNotPrime[j] = true;
        }
    }

    if (g % lcm) {
        printf("0");
        return 0;
    }

    g /= lcm;

    int ans = 1;

    for (int i = 2; i * i <= g; i++){
        if (isNotPrime[i]) continue;
        int factorCount = 0;
        while (!(g % i)){
            g /= i;
            factorCount++;
        } 
        if (!factorCount) continue;
        ans *= factorCount + 1;
    }

    if (g != 1) ans *= 2;
    printf("%d", ans);
}