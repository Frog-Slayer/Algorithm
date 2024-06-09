#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX_N = 5 * 10e5;

int N, M;
int degree[MAX_N + 1];//degree가 0 이하면 삭제된 노드다. 
int parent[MAX_N +1];//노드가 속한 그룹

vector<vector<int>> adj;
vector<pair<int, int>> dead_signs;
queue<int> q; //BFS를 위해 리프노드들을 넣는 큐

int find(int a) {
	if (parent[a] == a) return a;
	return parent[a] = find(parent[a]);
}

void uni(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return;
	parent[a] = b;
}

int main(){
	scanf("%d%d", &N, &M);
	adj.resize(N + 1);

	for (int i = 1; i <= N; i++) parent[i] = i;

	for (int i = 0; i < M; i++){
		int v, w;
		scanf("%d%d", &v, &w);
		adj[v].push_back(w);
		adj[w].push_back(v);

		degree[v]++;
		degree[w]++;
	}

	// degree가 1이면 리프노드다.
	for (int i = 1; i <= N; i++) {
		if (degree[i] == 1) {
			q.push(i);
		}
	}

	// BFS를 진행
	while (!q.empty()) {
		int front = q.front();
		q.pop();

		degree[front]--;

		for (int next : adj[front]) {
			if (degree[next] <= 0) continue;//삭제된 노드인 경우는 확인하지 않음
			uni(front, next);
			degree[next]--;

			if (degree[next] == 1) {//리프라서 곧 지워질 것. 큐에 넣음
				q.push(next);
			}
		}
	}

	// 각 노드들의 BFS 이후 결과 차수를 확인한다.
	for (int i = 1; i <= N; i++) {
		if (degree[i] > 0) {//사이클에 포함된 노드인 경우.
			for (int next: adj[i]) {
				if (degree[next] <= 0) {
					dead_signs.emplace_back(i, next);
				}
			}
		}
		else if (adj[i].size() == 1 && degree[find(i)] <=  0){//원래 리프노드 였고, 해당 노드가 속한 컴포넌트의 루트 노드가 삭제된 경우
			dead_signs.emplace_back(i, adj[i][0]);
		}
	}

	// 명시된 출력 방식에 따라 정렬한다.
	sort(dead_signs.begin(), dead_signs.end());

	printf("%lu\n", dead_signs.size());

	for (auto dead_sign : dead_signs) {
		printf("%d %d\n", dead_sign.first, dead_sign.second);
	}
}