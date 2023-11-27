#include <iostream>
#include <string.h>
using namespace std;

char S[200001];
int accSum[200001][26];
int q;
char a;
int l, r;

int main(){
    scanf("%s", S);
    int len = strlen(S);

    for (int j = 0; j < 26; j++){
        accSum[0][j] = (S[0] - 'a' == j);
    }

    for (int i = 1; i < len; i++){
        for (int j = 0; j < 26; j++){
            accSum[i][j] = accSum[i-1][j] + (S[i] - 'a' == j);
        }
    }


    scanf("%d", &q);

    for (int i = 0; i < q; i++){
        scanf(" %c %d %d", &a, &l, &r);
        printf("%d\n", accSum[r][a - 'a'] - (l > 0 ? accSum[l - 1][a - 'a'] : 0));
    }
}