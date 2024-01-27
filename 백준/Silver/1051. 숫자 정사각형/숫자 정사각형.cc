#include <iostream>
using namespace std;

int N, M;
char input[50][51];

int main(){
    scanf("%d%d", &N, &M);

    for (int i = 0; i < N; i++){
        scanf("%s", input[i]);
    }

    int ans = 1;

    for (int i = 0 ; i < N; i++){
        for (int j = 0; j < M; j++){
            char leftTop = input[i][j];

            for (int k = j; k < M; k++){
                if (input[i][k] == leftTop){
                    if (i + (k - j) >= N) continue;
                    if (input[i + k - j][j] == leftTop && input[i + k - j][k] == leftTop) {
                        ans = max(ans, (k - j + 1) * (k - j + 1));
                    }
                }
            }
        }
    }

    printf("%d", ans);

}