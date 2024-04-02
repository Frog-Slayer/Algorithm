#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<int> v, tmp, visit;

void solve(int cnt){
    if (cnt == M){
        for (int i = 0; i < M; i++){
            printf("%d ", tmp[i]);
        }
        printf("\n");
        return;
    }
    
    for (int i = 0; i < N; i++){
        if (visit[i]) continue;
        tmp.push_back(v[i]);
        visit[i] = true;
        solve(cnt + 1);
        visit[i] = false;
        tmp.pop_back();
    }
}

int main(){
    scanf("%d%d", &N, &M);

    visit.resize(N);

    for (int i = 0; i < N; i++){
        int n;
        scanf("%d", &n);
        v.push_back(n);
    }

    sort(v.begin(), v.end());
    solve(0);
}