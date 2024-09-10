#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;
#define all(v) v.begin(), v.end()

typedef pair<int, int> Point;
const int INF = 1e9;
const int MAX_SCORE = 1000;

int idx, sink, source;
vector<Point> points;
vector<vector<int>> adj_a, adj_b;

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

struct MCMF {
	vector<int> level;
	vector<vector<Edge*>> edges;

	void clear() {
		for (auto &ve : edges) {
			for (auto &e : ve) {
				delete e;
			}
			ve.clear();
		}
	}

	void resize(int N) {
		level.resize(N);
		edges.resize(N);
	}

	void add_edge(int i, int j, int capacity) {
		Edge *edge = new Edge(j, capacity);
		Edge *rev = new Edge(i, 0);

		edge->reverse = rev;
		rev->reverse = edge;

		edges[i].push_back(edge);
		edges[j].push_back(rev);
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

	int mcmf() {
		int ret = 0;
		while (bfs()){

			while (true) {
				int f = dfs(source, INF);
				ret += f;
				if (!f) break;
			}
		}

		return ret;
	}
} network;

void dfs(int cur, int parent, vector<vector<int>>& adj) {
	for (auto &child : adj[cur]) {
		if (child != parent) {
			network.add_edge(child + 1, cur + 1, INF);
			dfs(child, cur, adj);
		}
	}
}

int main() {
	int N;
	scanf("%d", &N);
	adj_a.resize(N), adj_b.resize(N);

	for (int i = 0; i < N - 1; i++) {//A
		int s, e;
		scanf("%d%d", &s, &e);
		adj_a[s].emplace_back(e);
		adj_a[e].emplace_back(s);
	}

	for (int i = 0; i < N - 1; i++) {//B
		int s, e;
		scanf("%d%d", &s, &e);
		adj_b[s].emplace_back(e);
		adj_b[e].emplace_back(s);
	}

	vector<int> score(N);

	sink = N + 1 ;
	network.resize(N + 2);

	for (int i = 0; i < N; i++) scanf("%d", &score[i]);

	int ans = 0;
	for (int i = 0; i < N; i++) {
		network.clear();
		dfs(i, -1, adj_a);
		dfs(i, -1, adj_b);

		for (int j = 0; j < N; j++) {
			network.add_edge(source, j + 1, MAX_SCORE + 1);
			network.add_edge(j + 1, sink, MAX_SCORE + 1 - score[j]);
		}

		int mcmf = network.mcmf();
		ans = max(ans, (MAX_SCORE + 1) * N - mcmf);
	}

	printf("%d", ans);
}