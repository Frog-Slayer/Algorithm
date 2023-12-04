#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 500;
const int INF = 555555;

int N, source, sink;
int camp[MAXN];
int work[MAXN + 2];
int sad[MAXN + 2][MAXN + 2];
int parent[MAXN + 2], level[MAXN + 2];

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
    for (int i = 0; i < MAXN + 2; i++) level[i] = -1;
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
    source = MAXN, sink = MAXN + 1;
    scanf("%d", &N);
    edges.resize(MAXN + 2);

    for (int i = 0; i < N; i++) {
        scanf("%d", &camp[i]);
        if (camp[i] == 1){
            addEdge(source, i, INF);
        }
        else if (camp[i] == 2){
            addEdge(i, sink, INF);
        }

    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &sad[i][j]);

            if (sad[i][j]) addEdge(i, j, sad[i][j]);
        }
    }

    int ans = 0;

    while (bfs()){
        for (int i = 0; i < MAXN + 2; i++) work[i] = 0;

        while (1) {
            int f = dfs(source, INF);
            if (!f) break;
            ans += f;
        }
    }

    printf("%d\n", ans);

    for (int i = 0; i < N; i++) {
        if (level[i] != -1) printf("%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        if (level[i] == -1) printf("%d ", i + 1);
    }
    printf("\n");
}