#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 2002;
const int INF = 2000000000; 
int N, M, K, result;
int flow[MAXN + 1][MAXN + 1], cap[MAXN + 1][MAXN + 1];
int parent[MAXN + 1];
vector<vector<int>> adj;

void maxFlow(int start, int end){
    while (1) {
        for (int i = 0; i <= N + M + 2; i++) parent[i] = -1;

        queue<int> q;
        q.push(start);

        while (!q.empty()){
            int front = q.front();
            q.pop();

            for (int next : adj[front]){
                if (cap[front][next] - flow[front][next] > 0 && parent[next] == -1){
                    q.push(next);
                    parent[next] = front;
                    if (next == end) break;
                }
            }            
        }

        if (parent[end] == -1) break;
        int f = INF;

        for (int i = end; i != start; i = parent[i]){
            f = min(f, cap[parent[i]][i] - flow[parent[i]][i]);
        }

        for (int i = end; i != start; i = parent[i]){
            flow[parent[i]][i] += f;
            flow[i][parent[i]] -= f;
        }
        result += f;
    }
}

int main(){
    scanf("%d%d%d", &N, &M, &K);
    adj.resize(N + M + 3);

    int source = 0;
    int extra = N + M + 1;
    int sink = N + M + 2;

    for (int i = 1; i <= N; i++){
        adj[source].push_back(i);
        adj[i].push_back(source);
        cap[source][i] = 1;

        adj[extra].push_back(i);
        adj[i].push_back(extra);
        cap[extra][i] = K;

        int cnt, t;
        scanf("%d", &cnt);
        for (int j = 0; j < cnt; j++) {
            scanf("%d", &t);
            adj[i].push_back(N + t);
            adj[N + t].push_back(i);
            cap[i][N + t]++;
        }
    }
    
    adj[0].push_back(extra);
    adj[extra].push_back(0);
    cap[0][extra] = K;

    for (int i = 1; i <= M; i++){
        adj[N + i].push_back(sink);
        adj[sink].push_back(N + i);
        cap[N + i][sink] = 1;
    }

    maxFlow(0, sink);

    printf("%d", result);
}