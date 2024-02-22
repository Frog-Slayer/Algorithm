#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 1000;
const int INF = 100000000;
int N, M, X;
int adj[MAXN][MAXN], revAdj[MAXN][MAXN];
int dist[MAXN], revDist[MAXN];

void dijk(int dist[MAXN], int adj[MAXN][MAXN]){
    for (int i = 0; i < N; i++) dist[i] = INF;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[X] = 0;
    pq.push({0, X});

    while (!pq.empty()){
        pair<int, int> top = pq.top();
        int d = top.first, cur = top.second;
        pq.pop();

        for (int i = 0; i < N; i++){
            if (!adj[cur][i]) continue;
            if (dist[i] > d + adj[cur][i]) {
                dist[i] = d + adj[cur][i];
                pq.push({dist[i], i});
            }
        }
    }
}

int main(){
    scanf("%d%d%d", &N, &M, &X);
    X--;
    for (int i = 0; i < M; i++){
        int s, e, t;
        scanf("%d%d%d", &s, &e, &t);
        adj[s-1][e-1] = t;
        revAdj[e-1][s-1] = t;
    }

    dijk(dist, adj);
    dijk(revDist, revAdj);

    int ans = 0;
    for (int i = 0; i < N; i++){
        ans = max(ans, dist[i] + revDist[i]);
    }

    printf("%d", ans);
}