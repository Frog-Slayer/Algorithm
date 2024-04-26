#include <iostream>
#include <vector>
using namespace std;

int N, M, C;
vector<int> jewels;
int dp[10][21][1 << 13];

int solve(int idx, int cap, int flag){
    if (idx == M) return -1;

    int ret = dp[idx][cap][flag];
    if (ret) return ret;


    for (int i = 0; i < N; i++){
        if ((1 << i) & flag) continue;
        int weight = jewels[i];

        if (cap >= weight) {
            ret = max(ret, 1 + solve(idx, cap - weight, flag | (1 << i)));
        }

        ret = max(ret, 1 + solve(idx + 1, C - weight, flag | (1 << i)));
    }

    return dp[idx][cap][flag] = ret;
}

int main(){
    scanf("%d%d%d", &N, &M, &C);

    for (int i = 0; i < N; i++){
        int jew;
        scanf("%d", &jew);
        if (jew > C) continue;
        jewels.push_back(jew);
    }

    N = jewels.size();

    int ans = solve(0, C, 0);

    printf("%d", ans);
}