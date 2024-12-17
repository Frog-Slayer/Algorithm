#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;
typedef pair<ll, ll> Point;

const int INF = 1e9;

Point operator-(Point &p1, Point &p2) {
	return Point(p1.first - p2.first, p1.second - p2.second);
}

ll dist_sq(Point &p1, Point &p2) {
	Point p = p1 - p2;
	return p.first * p.first + p.second * p.second;
}

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
};

int main() {
	fastio;

	int L, W, N;
	cin >> L >> W >> N;

	vector<Point> soldiers(N);

	for (int i = 0; i < N; i++) cin >> soldiers[i].first >> soldiers[i].second;

	Flow_Network network(N * 2);

	for (int i = 0; i < N; i++) {
		network.add_edge(i * 2, i * 2 + 1, 1);

		for (int j = 0; j < i; j++) {
			if (dist_sq(soldiers[i], soldiers[j]) <= 200 * 200) {
				network.add_edge(i * 2 + 1, j * 2, INF);
				network.add_edge(j * 2 + 1, i * 2, INF);
			}
		}

		if (soldiers[i].second <= 100) network.add_edge(network.source, i * 2, INF);

		if (soldiers[i].second >= W - 100) network.add_edge(i * 2 + 1, network.sink, INF);
	}

	int ans = network.dinic();

	cout << ans;

}