#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 100000;
int N, M, R, u, v;
int visitOrder[MAXN + 1];
int ord = 1;
vector<vector<int>> adj;
queue<int> q;

int main(){
	scanf("%d%d%d", &N, &M, &R);
	adj.resize(N+1);

	for (int i = 0; i < M; i++){
		scanf("%d%d", &u, &v);
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	
	for (int i = 1; i <= N; i++){
		sort(adj[i].begin(), adj[i].end(), greater<>());
	}

	q.push(R);
	visitOrder[R] = ord++;

	while (!q.empty()){
		int front = q.front();
		q.pop();
		for (int next : adj[front]){
			if (visitOrder[next]) continue;
			visitOrder[next] = ord++;
			q.push(next);
		}
	}

	for (int i = 1; i <= N; i++) printf("%d\n", visitOrder[i]);
}