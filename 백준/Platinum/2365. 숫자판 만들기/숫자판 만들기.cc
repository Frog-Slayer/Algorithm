#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int INF = 1e9;

struct Network {

	struct Edge {
		int to;
		int capacity;
		int flow;

		Edge(int _to, int _cap) : to(_to), capacity(_cap), flow(0) {}

		Edge *reverse;

		void push(int f) {
			flow += f;
			reverse->flow -= f;
		}
	};

	vector<vector<Edge*>> edges;
	vector<int> layer, work;
	int source = 0, sink = 0;

	Network(int N): source(N), sink(N + 1), edges(N + 2), layer(N + 2), work(N + 2) {}

	void add_edge(int u, int v, int c) {
		Edge *edge = new Edge(v, c);
		Edge *reverse_edge = new Edge(u, 0);

		edge->reverse = reverse_edge;
		reverse_edge->reverse = edge;

		edges[u].emplace_back(edge);
		edges[v].emplace_back(reverse_edge);
	}

	bool find_vertex_layer() { queue<int> q;
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
				return f_p; }
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

	void clear_flow_and_set_capacity(int cap) {
		for (int i = 0; i <= sink; i++) {
			for (auto &e : edges[i]) {
				e->flow = 0;
				if (e->capacity == 0) continue; //역방향
				if (i == source || e->to == sink) continue;
				e->capacity = cap; 
			}
		}
	}
};

int main() {
	fastio;

	int N;
	cin >> N;

	Network network(2 * N);
	int sum = 0;

	for (int i = 0; i < N; i++){
		int row;
		cin >> row;
		network.add_edge(network.source, i, row);
		sum += row;
	}

	for (int i = 0; i < N; i++){
		int col;
		cin >> col;
		network.add_edge(N + i, network.sink, col);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			network.add_edge(i, N + j, -1);
		}
	}

	int l = -1, r = 10000;

	while (l < r) {
		int m = (l + r) / 2;
		network.clear_flow_and_set_capacity(m);

		if (network.dinic() == sum) r = m;
		else l = m + 1;
	}

	network.clear_flow_and_set_capacity(r);
	network.dinic();

	cout << r << '\n';

	for (int i = 0; i < N; i++) {
		for (auto &e : network.edges[i]) {
			if (e->to == network.source) continue;
			cout << e->flow << ' ';
		}
		cout << '\n';
	}
}