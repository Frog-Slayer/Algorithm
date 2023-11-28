#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 400;
const int INF = 2000000000; 
int N, P, s, e, result;
int flow[MAXN + 1][MAXN + 1], cap[MAXN + 1][MAXN + 1];
int parent[MAXN + 1];
vector<vector<int>> adj;

void maxFlow(){
    while (1) {
        for (int i = 1; i <= N; i++) parent[i] = -1;

        queue<int> q;
        q.push(1);

        while (!q.empty()){
            int front = q.front();
            q.pop();

            for (int next : adj[front]){
                if (cap[front][next] - flow[front][next] > 0 && parent[next] == -1){
                    q.push(next);
                    parent[next] = front;
                    if (next == 2) break;
                }
            }            
        }

        if (parent[2] == -1) break;
        int f = INF;

        for (int i = 2; i != 1; i = parent[i]){
            f = min(f, cap[parent[i]][i] - flow[parent[i]][i]);
        }

        for (int i = 2; i != 1; i = parent[i]){
            flow[parent[i]][i] += f;
            flow[i][parent[i]] -= f;
        }
        result += f;
    }
}

int main(){
    scanf("%d%d", &N, &P);
    adj.resize(N + 1);

    for (int i = 0; i < P; i++) {
        scanf("%d%d", &s, &e);
        adj[s].push_back(e);
        adj[e].push_back(s);
        cap[s][e]++;
    } 

    maxFlow();

    printf("%d", result);


}