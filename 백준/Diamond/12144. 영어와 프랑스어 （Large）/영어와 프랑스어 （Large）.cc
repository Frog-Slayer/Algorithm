#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
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
};

vector<string> split(string input, string delimiter) {
	vector<string> ret; 
	long long pos = 0;
	string token = "";

	while((pos = input.find(delimiter)) != string::npos) {
		token = input.substr(0, pos);
		ret.push_back(token);
		input.erase(0, pos + delimiter.length());
	}
	ret.push_back(input);
	return ret;
}

void solve(int t) {
	int N;
	cin >> N;
	cin.ignore();

	int cnt = 0;
	unordered_map<string, int> words;
	int eng, fr;

	Flow_Network network(8000);

	for (int i = 0; i < N; i++) {
		string s;
		getline(cin, s);

		vector<string> v = split(s, " ");

		for (auto &word : v) {

			if (words.find(word) == words.end()){
				int idx = words[word] = ++cnt;
				network.add_edge(idx * 2, idx * 2 + 1, 1);
			}

			int idx = words[word];

			if (!i) network.add_edge(network.source, idx * 2, INF);
			else if (i == 1) network.add_edge(idx * 2 + 1, network.sink, INF); 
		}

		if (i < 2) continue;

		for (int j = 0; j < v.size(); j++) {
			for (int k = 0; k < v.size(); k++) {
				if (words[v[j]] == words[v[k]]) continue;
				network.add_edge(words[v[j]] * 2 + 1, words[v[k]] * 2, INF);
			}
		}
	}

	cout << "Case #" << t << ": " << network.dinic() << '\n';

}

int main() {
	fastio;

	int T;
	cin >> T;

	for (int i = 1; i <= T; i++) solve(i);
}