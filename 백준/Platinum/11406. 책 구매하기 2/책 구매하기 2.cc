#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define all(v) v.begin(), v.end()
#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

const int INF = 1e9;

int source, sink;

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
	vector<int> level, work;
	vector<vector<Edge*>> edges;

	void resize(int N) {
		work.resize(N);
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

		for (int &i = work[current]; i < edges[current].size(); i++){
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
			fill(all(work), 0);
			while (int f = dfs(source, INF)) {
				ret += f;
			}
		}

		return ret;
	}
} network;

int main() {
	fastio;
	int N, M;
	cin >> N >> M;

	network.resize(N + M + 2);

	source = 0;
	sink = N + M + 1;

	for (int i = 1; i <= N; i++) {
		int A;
		cin >> A;
		network.add_edge(source, i, A);
	}

	for (int i = 1; i <= M; i++) {
		int B;
		cin >> B;
		network.add_edge(N + i, sink, B);
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			int C;
			cin >> C;
			network.add_edge(j + 1, i + 1 + N, C);
		}
	}


	cout << network.mfmc();
}