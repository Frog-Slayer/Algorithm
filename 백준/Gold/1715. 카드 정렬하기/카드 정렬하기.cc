#include <iostream>
#include <queue>
using namespace std;

priority_queue<int, vector<int>, greater<int>> pq;

int main(){
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        int n;
        scanf("%d", &n);
        pq.push(n);
    }

    long long ans = 0;

    while (!pq.empty()){
        int a = pq.top();
        pq.pop();
        if (pq.empty()) {
            break;
        }
        int b = pq.top();
        pq.pop();
        pq.push(a + b);
        ans += (a + b);
    }

    printf("%lld", ans);
}