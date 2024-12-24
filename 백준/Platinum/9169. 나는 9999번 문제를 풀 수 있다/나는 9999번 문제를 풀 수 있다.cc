#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int INF = 1e9;

struct Flow_Network{

	struct Edge {
		int capacity = 0;
		int flow = 0;
	};

	vector<vector<Edge>> edges;
	vector<int> layer, work;
	int source = 0, sink = 0;

	Flow_Network(int N): source(0), sink(N + 1), layer(N + 2), work(N + 2), edges(N + 2, vector<Edge>(N + 2)) {}

	void add_edge(int u, int v, int c) {
		edges[u][v].capacity = c;
	}

	bool find_vertex_layer() {
		queue<int> q;
		q.push(source);

		fill(all(layer), -1);
		layer[source] = 0;

		while (!q.empty()) {
			int from = q.front();
			q.pop();

			for (int to = 0; to < edges[from].size(); to++) {
				if (layer[to] != -1) continue;
				Edge &edge = edges[from][to];
				if (edge.capacity - edge.flow > 0) {
					q.push(to);
					layer[to] = layer[from] + 1;
				}
			}
		}

		return layer[sink] != -1;
	}


	int augment_flow(int cur, int flow) {
		if (cur == sink) return flow;

		for (int &i = work[cur]; i < edges[cur].size(); i++) {
			Edge &edge = edges[cur][i];
			int to = i;
			int residual_capacity = edge.capacity - edge.flow;

			if (layer[to] != layer[cur] + 1) continue;
			if (residual_capacity <= 0) continue;

			int f_p = augment_flow(to, min(flow, residual_capacity));

			if (f_p > 0) {
				edge.flow += f_p;
				edges[to][cur].flow -= f_p;
				return f_p;
			}
		}
		return 0;
	}

	int dinic() {
		int max_flow = 0;

		while (find_vertex_layer()) {

			fill(all(work), 0);
		
			while (true) { 
				int f = augment_flow(source, INF);
				max_flow += f;
		
				if (!f) break;
			}
		}

		return max_flow;
	}
};

int main() {
	fastio;

	while (true) {
		int N, M;
		cin >> N >> M;

		if (!N && !M) break;

		Flow_Network network(N);

		vector<int> solvable(N + 1);

		for (int i = 1; i <= N; i++) {
			cin >> solvable[i];

			if (solvable[i]) network.add_edge(i, network.sink, 1);
			else network.add_edge(network.source, i, 1);
		}

		for (int i = 0; i < M; i++) {
			int a, b;
			cin >> a >> b;

			network.add_edge(a, b, 1);
			network.add_edge(b, a, 1);
		}

		cout << network.dinic() << '\n';
	}
}