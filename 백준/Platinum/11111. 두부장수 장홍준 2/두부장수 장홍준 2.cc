#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int INF = 1e9;
int N; int source, sink;

struct Edge{
    int to;
    int capacity;
    int flow = 0;
	int cost = 0;

    Edge *rev;
    
    Edge(int _to, int _capacity){
        to = _to;
        capacity = _capacity;
    }

    int left() {
        return capacity - flow;
    }

    void push(int amount){
        flow += amount;
        rev->flow -= amount;
    }
};

vector<vector<Edge*>> edges;

void add_edge(int from, int to, int cap, int cost) {
	Edge *u = new Edge(to, cap);
	Edge *v = new Edge(from, 0);

	u->cost = cost;
	v->cost = -cost;

	u->rev = v;
	v->rev = u;

	edges[from].emplace_back(u);
	edges[to].emplace_back(v);
}

int MCMF() {
	int ans = 0;
	
	while (true) {
		vector<int> parent(N + 2, -1), dist(N + 2, INF);
		vector<bool> visited(N + 2, false);
		vector<Edge*> path(N + 2);

		queue<int> q;
		q.push(source);
		dist[source] = 0;
		visited[source] = true;

		while (!q.empty()) {
			int cur = q.front();
			q.pop();

			visited[cur] = false;

			for (auto &edge: edges[cur]) {
				int resid_cap = edge->left();
				int next = edge->to;
				int cost = edge->cost;
				if (resid_cap > 0 && dist[next] > dist[cur] + cost) {
					parent[next] = cur;
					dist[next] = dist[cur] + cost; 
					path[next] = edge;

					if (!visited[next]) {
						q.push(next);
						visited[next] = true;
					}
				}
			}
		}

		if (parent[sink] == -1) break;
		int f = INF;

		for (int i = sink; i != source; i = parent[i]) {
			f = min(f, path[i]->left());
		}

		for (int i = sink; i != source; i = parent[i]) {
			path[i]->push(f);
			ans += f * path[i]->cost; 
		}
	}

	return ans;
}

void init(int _N) {
	N = _N;
	source = N, sink = N + 1;
	edges.resize(N + 2);
}

int main() {
	fastio;
	
	vector<vector<int>> tofu = {
		{10, 8, 7, 5, 0, 1},
		{8, 6, 4, 3, 0, 1},
		{7, 4, 3, 2, 0, 1},
		{5, 3, 2, 2, 0, 1},
		{0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 0, 0}
	};

	vector<int> dx = {0, -1, 1, 0}, dy = {1, 0, 0, -1};

	int n, m;
	cin >> n >> m;

	init(n * m);

	vector<string> arr(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int idx = i * m + j;

			add_edge(idx, sink, 1, 0);

			if ((i + j) % 2 == 0){
				add_edge(source, idx, 1, 0);
				for (int d = 0; d < 4; d++) {
					int nx = i + dx[d], ny = j + dy[d];
					if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;

					int cost = -tofu[arr[i][j] - 'A'][arr[nx][ny] - 'A'];

					int nidx = nx * m + ny;
					add_edge(idx, nidx, 1, cost);
				}
			}
		}
	}

	cout << -MCMF();
}