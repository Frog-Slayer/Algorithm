#include <iostream>
using namespace std;

long long factorial(int N){
    if (N <= 1) return 1;
    return factorial(N - 1) * N;
}

int main(){
    int N;
    scanf("%d", &N);

    printf("%lld", factorial(N));
}