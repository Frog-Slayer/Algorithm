#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200000;
const int MOD = 1000000007;
int N, M, C;
int color[MAXN + 1];
int nodeIdx;
vector<vector<int>> adj, tree;
vector<int> reIndexedColor;
vector<pair<int, int>> range;

void eulerTraverse(int node, int par){
    range[node].first = ++nodeIdx;
    reIndexedColor[nodeIdx] = color[node];

    for (int child : adj[node]){
        if (child == par) continue;
        eulerTraverse(child, node);
    }

    range[node].second = nodeIdx;
}

void makeTree(int node, int start, int end){
    tree[node].insert(tree[node].begin(), reIndexedColor.begin() + start, reIndexedColor.begin() + end + 1);
    sort(tree[node].begin(), tree[node].end());

    if (start == end) return;

    int mid = (start + end)/2;

    makeTree(node * 2, start, mid);
    makeTree(node * 2 + 1, mid + 1, end);
}

int query(int node, int start, int end, int left, int right, int val){
    if (end < left || right <start) return 0;
    if (left <= start && end <= right) {
        return upper_bound(tree[node].begin(), tree[node].end(), val) - tree[node].begin();
    }
    
    int mid = (start + end) / 2;

    return query(node * 2, start, mid, left, right, val) + query(node * 2 + 1, mid + 1, end, left, right, val);
}

int main(){
    scanf("%d%d%d", &N, &M, &C);
    adj.resize(N + 1);
    range.resize(N + 1);
    reIndexedColor.resize(N + 1);
    tree.resize(4 * (N + 1));

    for (int i = 1; i <= N; i++) {
        scanf("%d", &color[i]);
    }

    for (int i = 0; i < N - 1; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    eulerTraverse(1, 0);
    makeTree(1, 1, N);
    
    long long ans = 0;

    for (int i = 0; i < M; i++){
        int v, c;
        scanf("%d%d", &v, &c);
        ans += query(1, 1, N, range[v].first, range[v].second, c);
        ans %= MOD;
    }

    printf("%lld", ans);
}