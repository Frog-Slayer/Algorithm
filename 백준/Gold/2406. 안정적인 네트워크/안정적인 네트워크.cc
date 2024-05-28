#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_N = 1000;
typedef pair<int, pair<int, int>> PIP;

int n, m;
bool adj[MAX_N + 1][MAX_N + 1];
int parent[MAX_N + 1];
priority_queue<PIP, vector<PIP>, greater<>> pq;
vector<pair<int, int>> v;

int find(int a){
    if (parent[a] == a) return a;
    return parent[a] = find(parent[a]);
}

bool uni(int a, int b){
    a = find(a), b = find(b);
    if (a == b) return false;
    parent[a] = b;
    return true;
}


int main(){
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) parent[i] = i;

    for (int i = 0; i < m; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        uni(x, y);
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            int cost;
            scanf("%d", &cost);
            if (cost && (i != 1 && j != 1)) {
                pq.push({cost, {i, j}});
            }
        }
    }

    int X = 0, K = 0;

    while (!pq.empty()){
        PIP top = pq.top();
        pq.pop();

        int cost = top.first, a = top.second.first, b = top.second.second;
        if (!cost) continue;

        if (uni(a, b)) {
            v.emplace_back(a, b);
            X += cost;
            K++;
        }
    }

    printf("%d %d\n", X, K);

    for (int i = 0; i < K; i++) printf("%d %d\n", v[i].first, v[i].second);

    
}