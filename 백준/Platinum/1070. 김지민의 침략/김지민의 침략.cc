#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)); v.erase(unique(all(v)), v.end())
#define compressed(x) lower_bound(all(yy), x) - yy.begin()

const int MAX = 1e7;
const int INF = 1e9;
char map[50][51];
int cost[26];

struct Edge{
    int to;
    int capacity;
    int flow = 0;

    Edge *rev;
    
    Edge(int _to, int _capacity){
        to = _to;
        capacity = _capacity;
    }

    int left() {
        return capacity - flow;
    }

    void push(int amount){
        flow += amount;
        rev->flow -= amount;
    }
};

vector<vector<Edge*>> edges;
vector<int> level;
int source, sink;

void add_edge(int from, int to, int cap) {
	Edge *u = new Edge(to, cap);
	Edge *v = new Edge(from, 0);

	u->rev = v;
	v->rev = u;

	edges[from].emplace_back(u);
	edges[to].emplace_back(v);
}

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

	for (int i = 0; i < edges[current].size(); i++){
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

int mfmc() {
	int ret = 0;
	while (bfs()){
		while (true) {
			int f = dfs(source, INF);
			ret = (ret + f) % MAX;
			if (!f) break;
		}
	}

	return ret;
}

int main(){
	int N, M;
	int dx[] = {-1, 0, 0, 1}, dy[] = {0, -1, 1, 0};

	scanf("%d%d", &N, &M);

	edges.resize((N * M) * 2 + 2);
	level.resize((N * M) * 2 + 2);

	source = N * M * 2;
	sink = N * M * 2 + 1;

	for (int i = 0; i < N; i++) scanf("%s", map[i]);
	for (int i = 0; i < 26; i++) scanf("%d", &cost[i]);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int cur = i * M + j;

			if (map[i][j] == '-') continue;
			if (map[i][j] == '*') continue;

			else add_edge(cur * 2, cur * 2 + 1, cost[map[i][j] - 'A'] + MAX);

			if (i == 0 || j == 0 || i == N - 1 || j == M - 1) add_edge(source, cur * 2, INF);

			for (int d = 0; d < 4; d++) {
				int nx = i + dx[d], ny = j + dy[d]; 
				if (nx < 0 || ny < 0 || nx >= N || ny >= M || map[nx][ny] == '-') continue;

				int next = nx * M + ny;
				if (map[nx][ny] == '*') add_edge(cur * 2 + 1, sink, INF);
				else add_edge(cur * 2 + 1, next * 2, INF);
			}
		}
	}

	printf("%d", mfmc());
}