#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 50;

int N, node, root;
vector<vector<int>> adj;

int solve(int idx){
    if (idx == node) return 0;

    int childCount = 0;
    for (int child : adj[idx]){
        childCount += solve(child);
    }

    if (childCount == 0) return 1;
    return childCount;
}

int main(){
    scanf("%d", &N);
    adj.resize(N);

    for (int i = 0; i < N; i++) {
        int n;
        scanf("%d", &n);
        if (n == -1) root = i;
        else adj[n].push_back(i);
    }

    scanf("%d", &node);

    int ans = solve(root);

    printf("%d", ans);

}