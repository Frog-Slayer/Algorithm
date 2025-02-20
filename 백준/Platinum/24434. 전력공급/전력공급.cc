#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int INF = 1e9;

struct Flow_Network{

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

	Flow_Network(int N): source(N), sink(N + 1), edges(N + 2), layer(N + 2), work(N + 2) {}

	void add_edge(int u, int v, int c) {
		Edge *edge = new Edge(v, c);
		Edge *reverse_edge = new Edge(u, 0);

		edge->reverse = reverse_edge;
		reverse_edge->reverse = edge;

		edges[u].emplace_back(edge);
		edges[v].emplace_back(reverse_edge);
	}

	bool find_vertex_layer() {
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

	~Flow_Network() {
		for (auto &v : edges) {
			for (auto &e : v) {
				delete e;
			}
		}
	}
};

int main() {
	fastio;

	int T;
	cin >> T;

	while (T--) {
		int n, m;
		cin >> n >> m;

		Flow_Network network(n);

		int s = 0;

		for (int i = 0; i < n; i++) {
			int v;
			cin >> v;

			if (v < 0) network.add_edge(i, network.sink, -v);
			else{
				s += v;
				network.add_edge(network.source, i, v);
			}
		}

		for (int i = 0; i < m; i++) {
			int x, y, z;
			cin >> x >> y >> z;
			x--; y--;

			network.add_edge(x, y, z);
		}

		cout << s - network.dinic() << '\n';


	}
	
}

