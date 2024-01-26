#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<int> P;
vector<int> ans;

bool compare(int a, int b){
    if (P[a] != P[b]) return a < b;
    return a < b;
}

int main(){
    scanf("%d", &N);
    P.resize(N);
    
    for (int i = 0; i < N; i++){
        scanf("%d", &P[i]);
    }

    scanf("%d", &M);

    if (N == 1) printf("%d", 0);
    else {
        int minimum = 50, minOtherThanZero = 50;
        int minP, minOtherThanZeroP;

        for (int i = 0; i < N; i++){
            if (i){
                if (minOtherThanZero >= P[i]) {
                    minOtherThanZero = P[i];
                    minOtherThanZeroP = i;
                }
            }

            if (minimum >= P[i]){
                minimum = P[i];
                minP = i; 
            }
        }

        if (M - minOtherThanZero >= 0) {
            M -= minOtherThanZero;
            ans.push_back(minOtherThanZeroP);
        }
        else {
            printf("0");
            return 0;
        }

        while (1){
            if (M - minimum >= 0) {
                M -= minimum;
                ans.push_back(minP);
            } 
            else break;
        }

        sort(ans.begin(), ans.end(), compare);

        for (int i = ans.size() - 1; i >= 0; i--){
            for (int j = N - 1; j >= 0; j--){
                if (j <= ans[i]) continue;
                if (M - (P[j] - P[ans[i]])  >= 0) {
                    M -= (P[j] - P[ans[i]]);
                    ans[i] = j;
                    break;
                }
            }
        }

        sort(ans.begin(),ans.end(), greater());

        for (int i : ans){
            printf("%d", i);
        }
    }
}