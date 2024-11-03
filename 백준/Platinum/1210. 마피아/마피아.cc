#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 200 * 2;
const int INF = 10000000;

int N, M, source, sink;
int work[MAXN];
int sad[MAXN][MAXN];
int parent[MAXN], level[MAXN];

struct Edge{
    int to;
    int capacity;
    int flow = 0;

    Edge *reverse;
    
    Edge(int _to, int _capacity){
        to = _to;
        capacity = _capacity;
    }

    int capacityLeft() {
        return capacity - flow;
    }

    void pushFlow(int amount){
        flow += amount;
        reverse->flow -= amount;
    }
};

vector<vector<Edge*>> edges;

void addEdge(int i, int j, int capacity) {
    Edge *edge = new Edge(j, capacity);
    Edge *reverseEdge = new Edge(i, 0);

    edge->reverse = reverseEdge;
    reverseEdge->reverse = edge;

    edges[i].push_back(edge);
    edges[j].push_back(reverseEdge);
}

bool bfs(){
    queue<int> q;
    q.push(source);
    for (int i = 0; i < N * 2; i++) level[i] = -1;
    level[source] = 0;

    while (!q.empty()){
        int front = q.front();
        q.pop();

        for (auto edge : edges[front]){
            if (level[edge->to] != -1) continue;
            if (edge->capacityLeft() > 0) {
                q.push(edge->to); 
                level[edge->to] = level[front] + 1;
            }
        }
    }

    return level[sink] != -1;
}

int dfs(int current, int curFlow){
    if (current == sink) return curFlow;

    for (int& i = work[current]; i < edges[current].size(); i++){
        Edge* edge = edges[current][i];
        int to = edge->to; 
        int capacityLeft = edge->capacityLeft();
        if (level[to] != level[current] + 1) continue;
        if (capacityLeft <= 0) continue;

        int minFlow = dfs(to, min(curFlow, capacityLeft));
        if (minFlow > 0) {
            edge->pushFlow(minFlow);
            return minFlow;
        }
    } 
    return 0;
}

int main(){
    scanf("%d%d", &N, &M);
    edges.resize(2 * N);

    int s, t;
    scanf("%d%d", &s, &t);

    s--;
    t--;
    source  = 2 * s;
    sink = 2 * t + 1;

    int cost;
    for (int i = 0; i < N; i++){
        scanf("%d", &cost);
        int in = i * 2;
        int out = in + 1;
        addEdge(in, out, cost);
    }

    int a, b;
    for (int i = 0; i < M; i++){
        scanf("%d%d", &a, &b);
        a--; b--;

        int aIn = 2 * a;
        int aOut = aIn + 1;

        int bIn = 2 * b;
        int bOut = bIn + 1;

        addEdge(aOut, bIn, INF);
        addEdge(bOut, aIn, INF);
    }

    while (bfs()){
        for (int i = 0; i < 2 * N; i++) work[i] = 0;

        while (1){
            int f = dfs(source, INF);
            if (!f) break;
        }
    }

    queue<int> q;
    bool visited[MAXN] = {0, };

    q.push(source);
    visited[source] = true;
    while (!q.empty()){
        int front = q.front();
        q.pop();

        for (auto edge : edges[front]){
            int to = edge->to;
            if (visited[to]) continue;
            if (edge->capacityLeft() > 0){
                q.push(to);
                visited[to] = true;
            }
        }
    }

    for (int i = 0; i < 2 * N; i += 2) {
        if (visited[i] && !visited[i + 1]) printf("%d ", i / 2 + 1);
    }
}