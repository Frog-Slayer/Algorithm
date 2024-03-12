#include <iostream>
using namespace std;

const int MAXN = 100000;
int N;

int main(){
    scanf("%d", &N);
    if (N == 3) printf("-1");
    else if (!(N % 2)){
        for (int i = 1; i <= N; i++){
            int pos;

            if (i == 1) pos = N / 2; 
            else if (i == N) pos = N / 2 + 1; 
            else if (i <= N / 2) pos = i - 1;
            else pos = i + 1;
            
            printf("%d\n", pos);
        }
    }
    else {
        for (int i = 1; i <= N; i++){
            int pos;
            if (i == 1) pos = N / 2 + 1; 
            else if (i <= N / 2 + 1 || i > N / 2 + 2) pos = i - 1; 
            else pos = N;

            printf("%d\n", pos);
        }
    }
    
}