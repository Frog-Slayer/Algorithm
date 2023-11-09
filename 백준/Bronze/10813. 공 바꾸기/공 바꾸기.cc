#include <iostream>
using namespace std;

int N, M;
int ball[101];
int a, b;

int main(){
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) ball[i] = i;

    for (int i = 0; i < M; i++) {
        scanf("%d%d", &a, &b);
        swap(ball[a], ball[b]);
    }


    for (int i = 1; i <= N; i++) printf("%d ", ball[i]); 
}