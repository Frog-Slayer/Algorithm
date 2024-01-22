#include <iostream>
#include <vector>
#include <set>
using namespace std;

int N;
vector<int> P, S;
set<vector<int>> c;

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        int n;
        scanf("%d", &n);
        P.push_back(n);
    }
    
    c.insert(P);

    for (int i = 0; i < N; i++){
        int n;
        scanf("%d", &n);
        S.push_back(n);
    }

    int cnt = 0;
    bool infLoop = false;
    while (1){
        bool hasAnswer = true;
        vector<int> tmp(N);
        for (int i = 0; i < N; i++){
            if (P[i] % 3 != i % 3) {
                hasAnswer = false;
                break;
            }
        }
        if (hasAnswer) break; 

        for (int i = 0; i < N; i++){
            tmp[S[i]] = P[i];
        }

        for (int i = 0; i < N; i++){
            P[i] = tmp[i];
        } 

        cnt++;
        if (c.count(P)) {
            infLoop = true;
            break;
        }
        else c.insert(P);
    }

    if (infLoop) printf("-1");
    else printf("%d", cnt);

}