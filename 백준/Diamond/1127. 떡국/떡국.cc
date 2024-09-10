#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;
#define all(v) v.begin(), v.end()

const int MAX_N = 50;
const int INF = 1e9;

int N, source, sink, ans;
char coop[MAX_N][MAX_N + 1];
vector<vector<int>> company_guard, company_office;

struct Edge{
    int to;
    int capacity;
    int flow = 0;

    Edge *reverse;
    
    Edge(int _to, int _capacity){
        to = _to;
        capacity = _capacity;
    }

    int left() {
        return capacity - flow;
    }

    void push(int amount){
        flow += amount;
        reverse->flow -= amount;
    }
};

struct MCMF {
	vector<int> level;
	vector<vector<Edge*>> edges;

	void clear() {
		for (auto &ve : edges) {
			for (auto &e : ve) {
				delete e;
			}
			ve.clear();
		}
	}

	void resize(int N) {
		level.resize(N);
		edges.resize(N);
	}

	void add_edge(int i, int j, int capacity) {
		Edge *edge = new Edge(j, capacity);
		Edge *rev = new Edge(i, 0);

		edge->reverse = rev;
		rev->reverse = edge;

		edges[i].push_back(edge);
		edges[j].push_back(rev);
	}

	bool bfs(){
		for (int i = 0; i < level.size(); i++) level[i] = -1;

		queue<int> q;
		q.push(source);
		level[source] = 0;

		while (!q.empty()){
			int front = q.front();
			q.pop();

			for (auto edge : edges[front]){
				if (level[edge->to] != -1) continue;
				if (edge->left() > 0) {
					q.push(edge->to); 
					level[edge->to] = level[front] + 1;
				}
			}
		}

		return level[sink] != -1;
	}

	int dfs(int current, int flow){
		if (current == sink) return flow;

		for (int i = 0; i < edges[current].size(); i++){
			Edge *edge = edges[current][i];
			int to = edge->to; 
			int left = edge->left();

			if (level[to] != level[current] + 1 || left <= 0) continue;

			int min_flow = dfs(to, min(flow, left));

			if (min_flow > 0) {
				edge->push(min_flow);
				return min_flow;
			}
		} 

		return 0;
	}

	int mcmf() {
		int ret = 0;
		while (bfs()){

			while (true) {
				int f = dfs(source, INF);
				ret += f;
				if (!f) break;
			}
		}

		return ret;
	}
} network;

void solve(int company) {
	network.clear();
	vector<int> cnt(N);

	//guard가 있으면 office도 있음
	for (int guard : company_guard[company]) cnt[guard]++;
	for (int office : company_office[company]) cnt[office]++;

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (coop[i][j] == '0') continue; 
			if (!cnt[i]) {
				if (!cnt[j]) continue;//no conflict
				if (cnt[j] == 1) network.add_edge(j, sink, 1);
				else network.add_edge(source, sink, 1);//conflict
			}
			else if (cnt[i] == 1) {
				if (!cnt[j]) network.add_edge(i, sink, 1); 
				else if (cnt[j] == 1) {
					network.add_edge(i, j, 1);
					network.add_edge(j, i, 1);
				}
				else network.add_edge(source, i, 1);
			}
			else {
				if (!cnt[j]) network.add_edge(source, sink, 1); //conflict
				else if (cnt[j] == 1) network.add_edge(source, j, 1);
				else continue;//no conflict
			}
		}
	}

	ans += network.mcmf();
}

int main() {
	scanf("%d", &N);

	network.resize(N + 2);
	source = N, sink = N + 1;


	for (int i = 0; i < N; i++) scanf("%s", coop[i]);

	int K;
	scanf("%d", &K);
	company_guard.resize(K);
	company_office.resize(K);

	for (int i = 0; i < N; i++) {
		int cnt;
		scanf("%d", &cnt);

		for (int j = 0; j < cnt; j++) {
			int company;
			scanf("%d", &company);
			company_guard[company].emplace_back(i);
		}
	}
	
	for (int i = 0; i < N; i++) {
		int cnt;
		scanf("%d", &cnt);

		for (int j = 0; j < cnt; j++) {
			int company;
			scanf("%d", &company);
			company_office[company].emplace_back(i);
		}
	}

	for (int i = 0; i < K; i++) solve(i);

	printf("%d", ans);


}
