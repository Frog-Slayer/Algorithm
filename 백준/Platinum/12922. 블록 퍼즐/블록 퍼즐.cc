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

	int N;
	cin >> N;

	vector<int> dx = {-1, 0, 0, 1}, dy = {0, -1, 1, 0};
	
	auto stride = [&](int i, int j, int d, int s) {
		return tuple<int, int> (i + dx[d] * s, j + dy[d] * s);
	};

	Flow_Network network(N * N * 2);

	vector<string> board(N);
	for (int i = 0; i < N; i++) cin >> board[i];
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int in = i * N + j;
			in *= 2;
			int out = in + 1;

			if (board[i][j] == 'H') continue;

			if (board[i][j] == '.') network.add_edge(in, out, 1);
			else network.add_edge(in, out, INF);

			if (board[i][j] == 'b') network.add_edge(network.source, in, INF);
			else if (board[i][j] == '$') {
				network.add_edge(out, network.sink, INF);
				for (int d = 0; d < 4; d++) {
					auto [nx, ny] = stride(i, j, d, 3);
					if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;

					auto [ax, ay]  = stride(i, j, d, 2);
					auto [bx, by]  = stride(i, j, d, 1);

					if (board[nx][ny] == 'b' && (board[ax][ay] == 'b' || board[bx][by] == 'b')) { 
						cout << -1; 
						return 0;
					}
				}
			}

			for (int d = 0; d < 4; d++) {
				auto [nx, ny] = stride(i, j, d, 3);

				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (board[nx][ny] == 'H') continue;

				int nin = nx * N + ny;
				nin *= 2;

				auto [ax, ay]  = stride(i, j, d, 2);
				auto [bx, by]  = stride(i, j, d, 1);

				if (board[ax][ay] == 'b' || board[bx][by] == 'b') network.add_edge(out, nin, INF);
				else network.add_edge(out, nin, (board[ax][ay] == '.') + (board[bx][by] == '.'));
			}
		}
	}

	cout << network.dinic();

}