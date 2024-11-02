#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INF = 22222222;
const int MAXN = 200;
const int MAXD = 100;

int N, K, D;
int source, sink;
vector<vector<int>> adj;
int cap[MAXN + MAXD + 2][MAXN + MAXD + 2], flow[MAXN + MAXD + 2][MAXN + MAXD + 2];
int parent[MAXN + MAXD + 2], result;

void maxFlow(int src, int snk){

    while (1){
        queue<int> q;
        q.push(src);

        for (int i = src; i <= snk; i++) parent[i] = -1;

        while (!q.empty()){
            int here = q.front();
            q.pop();

            for (int there : adj[here]){
                if (parent[there] != -1) continue;
                int residCap = cap[here][there] - flow[here][there];
                if (residCap > 0){
                    parent[there] = here;
                    q.push(there);
                    if (there == snk) break;
                }
            }
        }

        if (parent[snk] == -1) break;
        int f = INF;

        for (int i = snk; i != src; i = parent[i]){
            int a = parent[i], b = i;
            int cf = cap[a][b] - flow[a][b];
            f = min(f, cf);
        }

        for (int i = snk; i != src; i = parent[i]){
            int a = parent[i], b = i;
            flow[a][b] += f;
            flow[b][a] -= f;
        }
        result += f;
    }

}

void addEdge(int a, int b, int capacity){
    adj[a].push_back(b);
    adj[b].push_back(a);
    cap[a][b] = capacity;
}

int main(){
    //유량 K
    scanf("%d%d%d", &N, &K, &D);

    adj.resize(N + D + 2);
    source = 0, sink = N + D + 1;

    for (int i = 1; i <= D; i++){
        int lim;
        scanf("%d", &lim);
        addEdge(N + i, sink, lim);
    }

    for (int i = 1; i <= N; i++) {
        addEdge(source, i, K);

        int Z;
        scanf("%d", &Z);

        for (int j = 1; j <= Z; j++){
            int food;
            scanf("%d", &food);
            addEdge(i, N + food, 1);
        }
    }

    maxFlow(source, sink);
    printf("%d", result);
}