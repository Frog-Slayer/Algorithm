#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<long long> v;

void solve(long long n){
    v.push_back(n);
    for (int i = (n % 10) - 1; i >= 0; i--){
        solve(n * 10 + i);
    }
}

int main(){
    int N;
    scanf("%d", &N);

    for (int i = 0; i < 10; i++) solve(i);

    sort(v.begin(), v.end());

    if (N > v.size()) printf("-1");
    else printf("%lld", v[N - 1]);
}