#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;
#define all(v) v.begin(), v.end()

typedef pair<int, int> Point;
const int MAX_N = 50;
const int INF = 1e3;

int source, sink, ans;

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

struct MFMC {
	vector<int> level;
	vector<vector<Edge*>> edges;

	void resize(int N) {
		level.resize(N);
		edges.resize(N);
	}

	void clear() {
		for (auto &ve : edges) {
			for (auto &e : ve) delete e;
			ve.clear();
		}
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

	int mfmc() {
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

int main() {
	int N, M, K;
	scanf("%d%d%d", &N, &M, &K);

	source = 0, sink = N + M + 1;
	network.resize(N + M + 2);

	vector<pair<int, int>> uv;

	for (int i = 0; i < K; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		uv.emplace_back(u, v);
	}
	
	int min_diff = INF;
	vector<int> ans;

	for (int i = 1; i <= M; i++) { 
		network.clear();

		for (int j = 1; j <= M; j++) network.add_edge(source, j, i == j ? INF : 1); 

		for (int j = M + 1; j <= M + N; j++) network.add_edge(j, sink, 1);

		for (auto &[u, v] : uv) network.add_edge(u, v + M, INF);
		
		int mfmc = network.mfmc();

		if (min_diff > mfmc) {
			min_diff = mfmc;
			ans.clear();
			queue<int> q;
			q.push(source);
			vector<bool> visited(N + M + 2);
			visited[0] = true;

			while (!q.empty()){
				int front = q.front();
				q.pop();

				for (auto edge : network.edges[front]){
					if (edge->left() > 0 && !visited[edge->to]) {
						visited[edge->to] = true;
						q.push(edge->to); 
					}
				}
			}

			for (int i = 1; i <= M; i++) if (visited[i]) ans.emplace_back(i);
		}
	}

	printf("%ld\n", ans.size());
	for (int &a : ans) printf("%d ", a);
}