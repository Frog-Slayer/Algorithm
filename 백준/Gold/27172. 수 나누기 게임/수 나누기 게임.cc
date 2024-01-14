#include <iostream>
using namespace std;

const int MAXN = 100000;
const int MAXCARD = 1000000;
int N;
int x[MAXN];
int score[MAXCARD + 1];
bool card[MAXCARD + 1];

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        scanf("%d", &x[i]);
        card[x[i]] = true;
    }

    for (int i = 0; i < N; i++){
        for (int j = x[i]; j <= MAXCARD; j += x[i]){
            if (card[j]){
                score[x[i]]++;
                score[j]--;
            }
        }
    }

    for (int i = 0; i < N; i++) printf("%d ", score[x[i]]);
}