#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 100;
const int MAXM = 100;
const int INF = 4444444;
int N, M;
int cap[MAXN + MAXM + 2][MAXN + MAXM + 2], flow[MAXN + MAXM + 2][MAXN + MAXM + 2], cost[MAXN + MAXM + 2][MAXN + MAXM + 2];
int parent[MAXN + MAXM + 2];
int dist[MAXN + MAXM + 2];
bool visited[MAXN + MAXM + 2];
int cnt, minTotal, source, sink;
vector<vector<int>> adj;

void maxFlow(int source, int sink){
    while (1){
        for (int i = source; i <= sink; i++) {
            parent[i] = -1;
            dist[i] = INF;
            visited[i] = false;
        }

        queue<int> q;
        q.push(source);
        dist[source] = 0;
        visited[source] = true;

        while (!q.empty()){
            int here = q.front();
            q.pop();
            visited[here] = false;

            for (int there : adj[here]){
                int residCap = cap[here][there] - flow[here][there];
                if (residCap > 0 && dist[there] > dist[here] + cost[here][there]) {
                    parent[there] = here;
                    dist[there] = dist[here] + cost[here][there];

                    if (!visited[there]) {
                        q.push(there);
                        visited[there] = true;
                    }
                }
            }
        }

        if (parent[sink] == -1) break;
        int f = INF;

        for (int i = sink; i != source; i = parent[i]){
            int here = parent[i], there = i;
            int residCap = cap[here][there] - flow[here][there];
            f = min(f, residCap);
        }

        for (int i = sink; i != source; i = parent[i]){
            int here = parent[i], there = i;
            flow[here][there] += f;
            flow[there][here] -= f;
            minTotal += f * cost[here][there];
        }
        cnt += f;
    }
}

void addEdge(int from, int to, int capacity){
    adj[from].push_back(to);
    adj[to].push_back(from);
    cap[from][to] = capacity;
}

int main(){
    scanf("%d%d", &N, &M);
    source = 0, sink = N + M + 1;
    adj.resize(N + M + 2);

    int bookCnt;
    for (int i = 1; i <= N; i++){
        scanf("%d", &bookCnt);
        addEdge(source, i, bookCnt);
    }

    for (int i = N + 1; i <= N + M; i++){
        scanf("%d", &bookCnt);
        addEdge(i, sink, bookCnt);
    } 

    int lim;
    for (int j = N + 1; j <= N + M; j++){
        for (int i = 1; i <= N; i++) {
            scanf("%d", &lim);
            addEdge(i, j, lim);
        }
    }

    int deliveryCost;
    for (int j = N + 1; j <= N + M; j++){
        for (int i = 1; i <= N; i++) {
            scanf("%d", &deliveryCost);
            cost[i][j] = deliveryCost;
            cost[j][i] = -deliveryCost;
        }
    }


    maxFlow(source, sink);

    printf("%d\n%d", cnt, minTotal);


}