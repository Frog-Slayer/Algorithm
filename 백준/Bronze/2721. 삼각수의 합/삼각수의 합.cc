#include <iostream>
using namespace std;

int W[301];

int main(){
    int T;
    scanf("%d", &T);

    for (int i = 1; i <= 300; i++){
        W[i] = W[i-1] + (i + 1) * (i + 2) / 2 * i;
    }

    while (T--){
        int n;
        scanf("%d", &n);
        
        printf("%d\n", W[n]);
    }
}