#include <iostream>
#include <queue>
#include <map>
#include <vector>

using namespace std;

const int INF = 2000000000;
const int MAXN = 10000;

int n, m, result, k, h;
char city[100][101];
vector<vector<int>> adj;
int parent[2 * MAXN];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

map<pair<int, int>, int> capa, flow;

void maxFlow(int source, int sink){
    while (1) {
        for (int i = 0; i < 2 * n * m; i++) parent[i] = -1;

        queue<int> q;
        q.push(source);

        while (!q.empty()){
            int front = q.front();
            q.pop();

            for (int next : adj[front]){
                if (capa[{front, next}] - flow[{front, next}] > 0 && parent[next] == -1){
                    q.push(next);
                    parent[next] = front;
                    if (next == sink) break;
                }
            }            
        }

        if (parent[sink] == -1) break;

        for (int i = sink; i != source; i = parent[i]){
            flow[{parent[i], i}]++;
            flow[{i, parent[i]}]--;
        }
        result ++;
    }
}

int main(){
    scanf("%d%d", &n, &m);
    adj.resize(2 * n * m);

    for (int i = 0; i < n; i++){
        scanf("%s", city[i]);
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            int num = i * m + j;
            int in = 2 * num;
            int out = in + 1;

            if (city[i][j] == '#') continue;
            if (city[i][j] == 'K') k = out;
            if (city[i][j] == 'H') h = in;

            //내부
            adj[in].push_back(out);
            adj[out].push_back(in);
            capa[{in, out}] = 1;

            //인접
            for (int d = 0; d < 4; d++){
                int nx = i + dir[d][0]; 
                int ny = j + dir[d][1]; 

                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (city[nx][ny] == '#') continue;
                if (city[i][j] == 'K' && city[nx][ny] == 'H') {
                    printf("-1");
                    return 0;
                }

                int nNum = nx * m + ny;
                int nIn = 2 * nNum;
                int nOut = nIn + 1;

                adj[out].push_back(nIn);
                adj[nIn].push_back(out);
                capa[{out, nIn}] = INF;
            }
        }
    }

    maxFlow(k, h);

    printf("%d", result);
}