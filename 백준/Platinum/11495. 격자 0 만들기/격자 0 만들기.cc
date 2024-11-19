#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()
#define lb(v, x) lower_bound(all(v), x) - v.begin()
#define ub(v, x) upper_bound(all(v), x) - v.begin()
#define compress(v) sort(all(v)); v.erase(unique(all(v)), v.end())


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
};

int main() {
	fastio;

	int T;
	cin >> T;

	vector<int> dx = {-1, 0, 0, 1}, dy = {0, -1, 1, 0};

	while (T--) {
		int n, m;
		cin >> n >> m;

		Network network(n * m);
		int source = n * m, sink = n * m + 1;

		int sum = 0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int num;
				cin >> num;

				sum += num;

				int idx = i * m + j;

				if ((i + j) & 1) {
					network.add_edge(source, idx, num);

					for (int d = 0; d < 4; d++) {
						int ni = i + dx[d], nj = j + dy[d];
						if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
						network.add_edge(idx, ni * m + nj, INF);
					}
				}
				else network.add_edge(idx, sink, num);
			}
		}

		cout << sum - network.dinic() << '\n';
	}
}