#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX_N = 5 * 10e5;

int N, M;
int edge_count[MAX_N + 1], parent[MAX_N +1];

vector<vector<int>> adj;
vector<pair<int, int>> dead_signs;
vector<int> roots;
queue<int> q;

int find(int a) {
	if (parent[a] == a) return a;
	return parent[a] = find(parent[a]);
}

void uni(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return;
	parent[a] = b;
}

int main(int argc, char* argv[]){
	scanf("%d%d", &N, &M);

	adj.resize(N + 1);
	for (int i = 1; i <= N; i++) parent[i] = i;

	for (int i = 0; i < M; i++){
		int v, w;
		cin >> v >> w;
		adj[v].push_back(w);
		adj[w].push_back(v);

		edge_count[v]++;
		edge_count[w]++;
	}

	/**
	  간선 a <-> b를 생각해보자. 
	  a 사이클, b 사이클: 표지판 없음
	  a 사이클, b 트리 : a -> b에 표지판
	  a 트리, b 사이클 : b -> a 표지판
	  a 트리, b 트리 : 리프노드에 연결된 간선들에 표지판 
  	*/

	// 어떤 사이클에 트리가 붙어있는 형태 -> 리프노드들을 하나씩 없애면서 들어가보기. 사이클 -> 트리를 잇는 곳에 표지판 세워짐

	// 얘들은 리프노드
	for (int i = 1; i <= N; i++) {
		if (edge_count[i] == 1) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int front = q.front();
		q.pop();
		edge_count[front]--;

		for (int next : adj[front]) {
			if (!edge_count[next]) continue;
			uni(front, next);
			edge_count[next]--;

			if (edge_count[next] == 1) {//이제 리프라서 지워질 거임
				q.push(next);
			}
		}
	}

	// 사이클에 트리가 붙어 있는 형태
	for (int i = 1; i <= N; i++) {
		//printf("edge_count[%d] = %d\n", i, edge_count[i]);
		if (edge_count[i] > 0) {//얘는 사이클
			for (int connected : adj[i]) {
				if (!edge_count[connected]) {
					dead_signs.emplace_back(i, connected);
				}
			}
		}
		else if (adj[i].size() == 1 && edge_count[find(i)] <=  0){
			dead_signs.emplace_back(i, adj[i][0]);
		}
	}
	

	sort(dead_signs.begin(), dead_signs.end());

	printf("%lu\n", dead_signs.size());

	for (auto dead_sign : dead_signs) {
		printf("%d %d\n", dead_sign.first, dead_sign.second);
	}
}