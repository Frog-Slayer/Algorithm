#include <iostream>
#include <vector>
using namespace std;;

vector<int> seq;

int main(){
    int N;

    scanf("%d", &N);
    for (int i = 0; i < N; i++){
        int a;
        scanf("%d", &a);
        seq.push_back(a);
    }

    if (N == 1) printf("A");
    else if (N == 2){
        if (seq[0] == seq[1]) printf("%d", seq[0]);
        else printf("A");
    }
    else {
        bool hasAnswer = true;
        int a  = 0;
        if (seq[0] != seq[1]) a = (seq[2] - seq[1]) / (seq[1] - seq[0]);

        int b = seq[1] - (a * seq[0]);

        for (int i = 1; i < N; i++){
            if (seq[i] != seq[i - 1] * a + b) {
                hasAnswer = false;
                printf("B");
                break;
            }
        }

        if (hasAnswer) {
            printf("%d", seq[N - 1] * a + b);
        }
    }
}