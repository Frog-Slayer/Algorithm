#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<int> v, ans;

void solve(int idx, int cnt){
    if (cnt == M){
        for (int i = 0; i < M; i++){
            printf("%d ", ans[i]);
        }
        printf("\n");
        return;
    }

    for (int i = idx; i < v.size(); i++){
        ans.push_back(v[i]);
        solve(i, cnt + 1);
        ans.pop_back();
    }
}


int main(){
    scanf("%d%d", &N, &M);
    v.resize(N);

    for (int i = 0; i < N; i++){
        scanf("%d", &v[i]);
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    solve(0, 0);
}