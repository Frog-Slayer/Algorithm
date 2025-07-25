#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;
const int MAXN = 3 * 1e5 + 1;

vector<int> cnt(MAXN);
vector<ll> ans(MAXN);
vector<vector<pair<int, ll>>> edges(MAXN);

void dfs(int root, int parent) { 
	cnt[root]++;

	for (auto [next, dist]: edges[root]) { 
		if (next == parent) continue;
		dfs(next, root);
		ans[1] += cnt[next] * dist;
		cnt[root] += cnt[next];
	}
}

void solve(int N, int root, int parent, ll weight) { 
	ans[root] = weight;

	for (auto [next, dist]: edges[root]) { 
		if (next == parent) continue;
		int csub = cnt[next];
		int rest = N - csub;
		solve(N, next, root, weight + dist * (rest - csub));
	}
}

int main() { 
	fastio;

	int N;
	cin >> N;

	for (int i = 0; i < N - 1; i++) { 
		int u, v, d;
		cin >> u >> v >> d;
		edges[u].emplace_back(v, d);
		edges[v].emplace_back(u, d);
	}

	dfs(1, 0);
	solve(N, 1, 0, ans[1]);
	
	for (int i = 1; i <= N; i++) cout << ans[i] << '\n';
}
