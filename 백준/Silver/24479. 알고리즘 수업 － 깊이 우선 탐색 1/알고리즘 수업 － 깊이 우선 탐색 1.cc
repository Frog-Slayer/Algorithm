#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100000;
int N, M, R, u, v;
int visitOrder[MAXN + 1];
int ord = 1;
vector<vector<int>> adj;

void dfs(int current){
	visitOrder[current] = ord++;
	for (int next : adj[current]){
		if (visitOrder[next]) continue;
		dfs(next);
	}
}


int main(){
	scanf("%d%d%d", &N, &M, &R);
	adj.resize(N+1);

	for (int i = 0; i < M; i++){
		scanf("%d%d", &u, &v);
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	
	for (int i = 1; i <= N; i++){
		sort(adj[i].begin(), adj[i].end());
	}
	
	dfs(R);

	for (int i = 1; i <= N; i++) printf("%d\n", visitOrder[i]);
}