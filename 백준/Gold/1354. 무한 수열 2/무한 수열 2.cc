#include <iostream>
#include <unordered_map>
using namespace std;

typedef long long ll;

ll N, P, Q, X, Y;
unordered_map<ll, ll> A;

long long solve(ll n){
    if (n <= 0) return A[n] = 1;
    if (A[n]) return A[n];

    return A[n] = solve(n / P - X) + solve(n / Q - Y);
}

int main(){
    scanf("%lld%lld%lld%lld%lld", &N, &P, &Q, &X, &Y);

    printf("%lld", solve(N));
}