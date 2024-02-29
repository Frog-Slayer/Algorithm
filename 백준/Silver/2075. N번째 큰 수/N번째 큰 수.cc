#include <iostream>
#include <queue>
using namespace std;

priority_queue<int, vector<int>, greater<int>> pq, tmp;

int main(){
    int N, n;
    scanf("%d", &N);

    for (int i = 0; i < N * N; i++){
        scanf("%d", &n);
        if (pq.size() < N) pq.push(n);
        else if (pq.top() < n){
            pq.pop();
            pq.push(n);
        }
    }
    printf("%d", pq.top());
}