#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 1001;
const int INF = 1000 * 100000;

int N, M;
int adj[MAXN][MAXN];
int dist[MAXN];
int from[MAXN];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

int dijk(bool isFirst){
	for (int j = 1; j <= N; j++) dist[j] = INF;

	pq.push({0, 1});
	dist[1] = 0;

	while (!pq.empty()){
		pair<int, int> top = pq.top();
		pq.pop();

		if (top.first > dist[top.second]) continue;

		for (int i = 1; i <= N; i++){
			if (i == top.second) continue;
			if (!adj[top.second][i]) continue;
			int d = adj[top.second][i] + dist[top.second];
			if (dist[i] >= d) {
				dist[i] = d;
				pq.push({d, i}); 
				if (isFirst) from[i] = top.second; 
			}
		}
	}
	return dist[N];
}

int main(){
	scanf("%d%d", &N, &M);

	for (int i = 0; i < M; i++){
		int a, b, t;
		scanf("%d%d%d", &a, &b, &t);
		adj[a][b] = adj[b][a] = t;
	}

	dijk(true);
	int d = dist[N];
	int ans = 0;

	if (d == INF) {
		printf("-1");
		return 0;
	}

	for (int i = N; from[i]; i = from[i]){
		int a = i, b = from[i];
		int origin = adj[a][b];

		adj[a][b] = 0;
		adj[b][a] = 0;
		int dst = dijk(false);

		if (dst == INF) {
			ans = -1; 
			break;
		}

		ans = max(ans, dst - d); 
		adj[a][b] = origin;
		adj[b][a] = origin;
	}

	printf("%d", ans);
}