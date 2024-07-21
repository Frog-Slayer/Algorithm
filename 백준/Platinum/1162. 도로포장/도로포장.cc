#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tp;

const ll INF = 10000000000;
const int MAX_N = 10000;
const int MAX_K = 20;

int N, M, K;
priority_queue<tp, vector<tp>, greater<>> pq;
vector<vector<pair<int, int>>> v;
ll dist[MAX_N][MAX_K + 1];//dp[i][j] = 0에서 i까지, j개의 도로를 포장했을 때의 최단 거리

void solve() {
	for (int i = 1; i < MAX_N; i++) for (int j = 0; j <= MAX_K; j++) dist[i][j] = INF;
	pq.push({0, 0, 0});

	while (!pq.empty()){
		ll total;
		int cur, paved;
		tie(total, cur, paved) = pq.top();
		pq.pop();

		if (total > dist[cur][paved]) continue;

		for (int i = 0; i < v[cur].size(); i++) {
			int next = v[cur][i].first;
			int cost = v[cur][i].second;

			if (paved < K && dist[next][paved + 1] > total) {
				dist[next][paved + 1] = total;
				pq.push({total, next, paved + 1});
			}

			if (dist[next][paved] > total + cost) {
				dist[next][paved] = total + cost;
				pq.push({total + cost, next, paved});
			}
		}
	}
}

int main(){
	scanf("%d%d%d", &N, &M, &K);
	v.resize(N + 1);

	for (int i = 0; i < M; i++) {
		int s, e, t;
		scanf("%d%d%d", &s, &e, &t);
		s--;
		e--;
		v[s].emplace_back(e, t);
		v[e].emplace_back(s, t);
	}

	solve();

	ll ans = INF;

	for (int i = 0; i <= K; i++) ans = min(ans, dist[N - 1][i]);

	printf("%lld", ans);


}