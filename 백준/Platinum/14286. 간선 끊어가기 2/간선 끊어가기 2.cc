#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int INF = 2000000000;
const int MAXN = 500;

int n, m, a, b, c, result, s, t;
vector<vector<int>> adj;
int capa[2 * MAXN + 1][2 * MAXN + 1], flow[2 * MAXN + 1][2 * MAXN + 1], parent[2 * MAXN + 1];

void maxFlow(int source, int sink){
    while (1) {
        for (int i = 0; i <= 2 * n; i++) parent[i] = -1;

        queue<int> q;
        q.push(source);

        while (!q.empty()){
            int front = q.front();
            q.pop();

            for (int next : adj[front]){
                if (capa[front][next] - flow[front][next] > 0 && parent[next] == -1){
                    q.push(next);
                    parent[next] = front;
                    if (next == sink) break;
                }
            }            
        }

        if (parent[sink] == -1) break;
        int f = INF;

        for (int i = sink; i != source; i = parent[i]){
            f = min(f, capa[parent[i]][i] - flow[parent[i]][i]);
        }

        for (int i = sink; i != source; i = parent[i]){
            flow[parent[i]][i] += f;
            flow[i][parent[i]] -= f;
        }
        result += f;
    }
}

int main(){
    scanf("%d%d", &n, &m);
    adj.resize(2 * n  + 1);

    for (int i = 1; i <= n; i++) {
        int in = i * 2 - 1;
        int out = i * 2;

        adj[in].push_back(out);
        adj[out].push_back(in);
        capa[in][out] = INF;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &c);
        int aIn = 2 * a - 1;
        int aOut = 2 * a;
        int bIn = 2 * b - 1;
        int bOut = 2 * b;

        adj[aOut].push_back(bIn);
        adj[bOut].push_back(aIn);
        capa[aOut][bIn] = c;
        capa[bOut][aIn] = c;
    }
    scanf("%d%d", &s, &t);

    maxFlow(2 * s, t * 2 - 1);

    printf("%d", result);
}