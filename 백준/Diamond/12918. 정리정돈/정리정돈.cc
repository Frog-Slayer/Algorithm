#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const double INF = 1e9;

int N;
int source, sink;

struct Edge{
    int to;
    int capacity;
    int flow = 0;
	double cost = 0;

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

void add_edge(int from, int to, int cap, double cost) {
	Edge *u = new Edge(to, cap);
	Edge *v = new Edge(from, 0);

	u->cost = cost;
	v->cost = -cost;

	u->rev = v;
	v->rev = u;

	edges[from].emplace_back(u);
	edges[to].emplace_back(v);
}

double MCMF() {
	double ans = 0;
	
	while (true) {
		vector<int> parent(N + 2, -1);
		vector<double> dist(N + 2, INF);
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
				double  cost = edge->cost;
                
				if (resid_cap > 0 && dist[next] > dist[cur] + cost + 1e-9) {
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

void init() {
	source = N, sink = N + 1;
	edges.resize(N + 2);
}

int main() {
	fastio;

	int n;
	cin >> n;
	N = 2 * n;
	
	init();

	using Point = pair<int, int>;

	vector<Point> v(n);

	for (int i = 0; i < n; i++) {
		cin >> v[i].first >> v[i].second;
		v.emplace_back(-v[i].first, v[i].second);

		add_edge(source, i, 1, 0);
		add_edge(i + n, sink, 1, 0);
	}

	auto dist = [](Point &p1, Point &p2) -> double{
		int xdiff = p1.first - p2.first;
		int ydiff = p1.second - p2.second;

		return sqrt(xdiff * xdiff + ydiff * ydiff);
	};

	for (int i = 0; i < n; i++) {
		for (int j = n; j < 2 * n; j++) {
			add_edge(i, j, 1, dist(v[i], v[j]) / 2.0);
		}
	}

	cout << fixed;
	cout.precision(3);

	cout << MCMF();

}