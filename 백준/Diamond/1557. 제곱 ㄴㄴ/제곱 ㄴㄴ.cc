#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const ll MAXN = 1e10;

ll n;
int mobi[1000001];

void findMobi(){
    mobi[1] = 1;
    for (int i = 1; i <= 1e6; i++){
        for (int j = 2 * i; j <= 1e6; j += i){
            mobi[j] -= mobi[i];
        }
    }
}


ll countSquareFreeUnder(ll x){
    ll ret = 0;
    for (long long i = 1; i * i <= x; i++){
        ret += mobi[i] * (x / (i * i));
    }
    return ret;
}

int main(){
    scanf("%lld", &n);
    findMobi();

    ll left = 1, right = 1e12;
    ll ans = 0;
    
    while (left <= right){
        ll mid = (left + right) / 2;
        ll cnt = countSquareFreeUnder(mid);
        
        if (cnt == n) {
            if (countSquareFreeUnder(mid - 1) == n - 1) {
                ans = mid;
                break;
            }
            else right = mid - 1;

        }
        else if (cnt > n) right = mid - 1;
        else left = mid + 1;
    }

    printf("%lld", ans);
}