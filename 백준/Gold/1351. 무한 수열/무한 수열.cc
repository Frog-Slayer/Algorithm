#include <iostream>
#include <unordered_map>
using namespace std;

typedef long long ll;

ll N, P, Q;
unordered_map<ll, ll> A;

ll solve(ll n){
    if (A[n]) return A[n];

    return A[n] = solve(n / P) + solve(n / Q);
}

int main(){
    scanf("%lld%lld%lld", &N, &P, &Q);

    A[0] = 1;
    
    printf("%lld", solve(N));
}