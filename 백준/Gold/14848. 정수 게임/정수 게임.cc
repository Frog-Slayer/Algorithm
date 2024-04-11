#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b){
    ll r;
    if (a < b) swap(a, b);

    while (b){
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main(){
    int N, K;
    scanf("%d%d", &N, &K);

    vector<int> A(K);

    for (int i = 0; i < K; i++){
        scanf("%d", &A[i]);
    }

    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());

    K = A.size();
    int sum = 0;

    for (int i = 1; i < (1 << K); i++){
        ll lcm = 1;
        ll cnt = -1;

        for (int j = 0; j < K; j++){
            if ((1 << j) & i){
                cnt *= -1;
                lcm = lcm * A[j] / gcd(lcm, A[j]);
            }
        }

        sum += cnt * (N / lcm);
    }

    printf("%d", N - sum);


}