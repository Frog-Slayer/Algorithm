#include <iostream>
using namespace std;

typedef long long ll;

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
    int g, l;

    scanf("%d%d", &g, &l);

    ll prod = 1LL * g * l; 
    int a, b;
    ll minSum = g + l;

    for (int i = g; i <= l; i += g){
        if (prod % i) continue;
        if (gcd(i, prod/i) == g && (i + prod/i <= minSum)) {
            minSum = i + prod/i;
            a = i;
            b = prod / i; 
        }
    } 

    if (a > b) swap(a, b);

    printf("%d %d", a, b);


}