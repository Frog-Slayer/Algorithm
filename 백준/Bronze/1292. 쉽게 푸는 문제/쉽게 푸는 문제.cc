#include <iostream>
using namespace std;

int main(){
    int A, B;
    int arr[1001];
    
    int cur = 1;
    for (int i = 1; i <= 1000; ){
        int j = 0;
        for (j = 0; j < cur; j++){
            if (i + j > 1000) break;
            arr[i + j] = arr[i + j - 1] + cur;
        }
        if (i + j > 1000) break;
        i += j;
        cur++;
    }

    scanf("%d%d", &A, &B);

    printf("%d", arr[B] - arr[A - 1]);

}