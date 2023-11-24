#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;
int N;
int A, B, W;
long long ans;
vector<vector<pair<int, int>>> adj;

long long solve(int cur, int parent){
    long long edgeWeightSum = 1;//리프노드일 때
    for (pair<int, int> edge : adj[cur]){
        if (edge.first == parent) continue;
        int next = edge.first;
        int weight = edge.second;

        long long subtree = solve(next, cur);
        subtree *= weight;
        subtree %= MOD;

        ans += subtree * edgeWeightSum;
        ans %= MOD;

        edgeWeightSum += subtree;
        edgeWeightSum %= MOD;
    }

    return edgeWeightSum;
}

int main(){
    scanf("%d", &N);
    adj.resize(N+1);
    for (int i = 0; i < N - 1; i++){
        scanf("%d%d%d", &A, &B, &W);
        adj[A].emplace_back(B, W);
        adj[B].emplace_back(A, W);
    }

    solve(1, 0);
    printf("%lld", ans);

}