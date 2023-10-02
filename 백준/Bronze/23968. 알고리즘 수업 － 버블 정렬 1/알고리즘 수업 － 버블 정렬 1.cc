#include <iostream>
using namespace std;

int N, K;
int A[10000];

int main(){
    scanf("%d%d", &N, &K);
    
    for (int i = 0; i < N; i++){
        scanf("%d", &A[i]);
    }

    int cnt = 0;
    for (int i = N - 1; i > 0; i--){
        for (int j = 0; j < i; j++){
            if (A[j] > A[j+1]) {
                cnt++;
                swap(A[j], A[j+1]);
                if (cnt == K) printf("%d %d", A[j], A[j+1]);
            }
        }
    }
    if (cnt < K) printf("-1");
}