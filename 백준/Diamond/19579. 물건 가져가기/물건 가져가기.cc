#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;
#define all(v) v.begin(), v.end()

typedef pair<int, int> Point;
const int INF = 1e9;

int idx, sink, source;
vector<Point> points;

struct Edge{
    int to;
    int capacity;
    int flow = 0;

    Edge *reverse;
    
    Edge(int _to, int _capacity){
        to = _to;
        capacity = _capacity;
    }

    int left() {
        return capacity - flow;
    }

    void push(int amount){
        flow += amount;
        reverse->flow -= amount;
    }
};

vector<vector<Edge*>> edges;

void add_edge(int i, int j, int capacity) {
    Edge *edge = new Edge(j, capacity);
    Edge *rev = new Edge(i, 0);

    edge->reverse = rev;
    rev->reverse = edge;

    edges[i].push_back(edge);
    edges[j].push_back(rev);
}

vector<int> level, work;

bool bfs(){
	for (int i = 0; i < level.size(); i++) level[i] = -1;

    queue<int> q;
    q.push(source);
    level[source] = 0;

    while (!q.empty()){
        int front = q.front();
        q.pop();

        for (auto edge : edges[front]){
            if (level[edge->to] != -1) continue;
            if (edge->left() > 0) {
                q.push(edge->to); 
                level[edge->to] = level[front] + 1;
            }
        }
    }

    return level[sink] != -1;
}

int dfs(int current, int flow){
    if (current == sink) return flow;

    for (int i = work[current]; i < edges[current].size(); i++){
        Edge *edge = edges[current][i];
        int to = edge->to; 
        int left = edge->left();

        if (level[to] != level[current] + 1 || left <= 0) continue;

        int min_flow = dfs(to, min(flow, left));

        if (min_flow > 0) {
            edge->push(min_flow);
            return min_flow;
        }
    } 

    return 0;
}

void mcmf() {

    while (bfs()){
		for (int i = 0; i < work.size(); i++) work[i] = 0;

        while (true) {
			int f = dfs(source, INF);
			if (!f) break;
        }
    }
}

int main() {
	int N, M;
	scanf("%d%d", &N, &M);
	edges.resize(N + 2), level.resize(N + 2), work.resize(N + 2);

	sink = N + 1;

	for (int i = 1; i <= N; i++) {
		int t;
		scanf("%d", &t);
		if (t >= 0) add_edge(source, i, t);
		else add_edge(i, sink, -t);
	}

	for (int i = 0; i < M; i++) {
		int s, e;
		scanf("%d%d", &s, &e);
		add_edge(s, e, INF);
	}

	mcmf();

	queue<int> q;
	q.push(0);
	vector<bool> visited(N + 2);
	int ans = 0;
	visited[0] = true;

	while (!q.empty()){
		int front = q.front();
		q.pop();

        for (auto edge : edges[front]){
			if (edge->left() > 0 && !visited[edge->to]) {
				visited[edge->to] = true;
				ans++;
                q.push(edge->to); 
            }
		}
	}

	printf("%d\n", ans);
	for (int i = 1; i <= N; i++) if (visited[i]) printf("%d ", i);

}
