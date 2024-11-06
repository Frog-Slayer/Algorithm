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
		int to;
		int capacity;
		int flow = 0;

		Edge(int _to, int _cap) : to(_to), capacity(_cap) {}

		Edge *reverse;

		void push(int f) {
			flow += f;
			reverse->flow -= f;
		}
	};

	vector<vector<Edge*>> edges;
	vector<int> layer, work;
	int source = 0, sink = 0;

	Flow_Network(int N): source(0), sink(N + 1), edges(N + 2), layer(N + 2), work(N + 2) {}

	void add_edge(int from, int to, int c) {
		Edge *edge = new Edge(to, c);
		Edge *reverse_edge = new Edge(from, 0);

		edge->reverse = reverse_edge;
		reverse_edge->reverse = edge;

		edges[from].emplace_back(edge);
		edges[to].emplace_back(reverse_edge);
	}

	bool find_augpath() {
		queue<int> q;
		q.push(source);

		fill(all(layer), -1);
		layer[source] = 0;

		while (!q.empty()) {
			int from = q.front();
			q.pop();

			for (auto &edge: edges[from]) {
				int to = edge->to;
				if (layer[to] != -1) continue;
				if (edge->capacity - edge->flow > 0) {
					q.push(to);
					layer[edge->to] = layer[from] + 1;
					if (to == sink) break;
				}
			}
		}

		return layer[sink] != -1;
	}


	int augment_flow(int cur, int flow) {
		if (cur == sink) return flow;

		for (int &i = work[cur]; i < edges[cur].size(); i++) {
			Edge *edge = edges[cur][i];
			int to = edge->to;
			int residual_capacity = edge->capacity - edge->flow;

			if (layer[to] != layer[cur] + 1) continue;
			if (residual_capacity <= 0) continue;

			int f_p = augment_flow(to, min(flow, residual_capacity));

			if (f_p > 0) {
				edge->push(f_p);
				return f_p;
			}
		}
		return 0;
	}

	int dinic() {
		int max_flow = 0;

		while (find_augpath()) {
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

	int N, K, D;
	cin >> N >> K >> D;

	Flow_Network network(N + D);

	for (int i = 1; i <= D; i++) {
		int M;
		cin >> M;
		network.add_edge(N + i, network.sink, M);
	}

	for (int i = 1; i <= N; i++) {
		network.add_edge(network.source, i, K);

		int Z;
		cin >> Z;

		for (int j = 0; j < Z; j++) {
			int food;
			cin >> food;
			network.add_edge(i, N + food, 1);
		}
	}

	cout << network.dinic();
}