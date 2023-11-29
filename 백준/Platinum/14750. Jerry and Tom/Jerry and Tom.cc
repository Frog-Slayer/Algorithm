#include <iostream>
#include <queue>
#include <vector>

#define POINT pair<int, int> 
using namespace std;

const int INF = 2000000000;
int n, k, h, m, x, y, result;
vector<POINT> points;
vector<POINT> holes;
vector<POINT> mice;
vector<pair<POINT, POINT>> segments;
vector<vector<int>> adj;
int capa[310][310], flow[310][310], parent[310];

int ccw(POINT p1, POINT p2, POINT p3){
    long long x1 = p1.first;
    long long y1 = p1.second;
    long long x2 = p2.first;
    long long y2 = p2.second;
    long long x3 = p3.first;
    long long y3 = p3.second;

    long long ret = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
    if (ret > 0) return 1;
    if (!ret) return 0;
    return -1;
}

bool isHoldOnCorner(POINT hole, POINT p){
    return (hole.first == p.first && hole.second == p.second);
}

bool isCrossing(pair<POINT, POINT> mouseToHole, pair<POINT, POINT> segment){
    POINT a = mouseToHole.first;
    POINT b = mouseToHole.second;
    POINT c = segment.first;
    POINT d = segment.second;

    int ab= ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);

    if (!ab && !cd){
        if (a > b) swap(a, b);
        if (c > d) swap(c, d);
        return c <= b && a <= d;
    }
    return ab <= 0 && cd <= 0;
}

void maxFlow(int source, int sink){
    while (1) {
        for (int i = source; i <= sink; i++) parent[i] = -1;

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
    scanf("%d%d%d%d", &n, &k, &h, &m);
    adj.resize(m + h + 2);

    for (int i = 0; i < n; i++){
        scanf("%d%d", &x, &y);
        points.emplace_back(x, y);
    }

    for (int i = 0; i < n; i++){
        segments.push_back({points[(i - 1 + n) % n], points[i]});
    }

    for (int i = 0; i < h; i++) {//hole
        scanf("%d%d", &x, &y);
        holes.emplace_back(x, y);
    }

    for (int i = 0; i < m; i++) {//mice
        scanf("%d%d", &x, &y);
        mice.emplace_back(x, y);
    }

    for (int i =0; i < m; i++) {
        for (int j = 0; j < h; j++) {
            pair<POINT, POINT> mouseToHole = {mice[i], holes[j]};
            int cnt = 0;
            for (int l = 0; l < segments.size(); l++) { 
                pair<POINT, POINT> segment = segments[l];
                cnt += isCrossing(mouseToHole, segment) && !(isHoldOnCorner(mouseToHole.second, segment.first));
            }
           
            if (cnt == 1) {
                adj[(i + 1)].push_back((m + 1) + j);
                adj[(m + 1) + j].push_back(i + 1);
                capa[(i + 1)][(m + 1) + j] = k;
            }
        }
    }

    int source = 0, sink = (m + h + 1);
    for (int i = 1; i <= m; i++) {
        adj[source].push_back(i);
        adj[i].push_back(source);
        capa[source][i] = 1;
    }    

    for (int i = m + 1; i <= m + h; i++) {
        adj[sink].push_back(i);
        adj[i].push_back(sink);
        capa[i][sink] = k;
    }

    maxFlow(source, sink);

    printf("%s", result == m ? "Possible" : "Impossible");
}