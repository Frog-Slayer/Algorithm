#include <iostream>
#include <vector>
using namespace std;
#define fastio cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false)

const int MAX_N = 1000;
vector<vector<int>> adj;
vector<int> weight;
int dp[MAX_N + 1][MAX_N + 1];

int solve(int cur, int parent, int lsp) {
	if (dp[cur][lsp]) return dp[cur][lsp];

	int special = weight[cur], not_special = weight[cur] - weight[lsp];

	for (int &child : adj[cur]) {
		if (child == parent) continue;
		special += solve(child, cur, cur);
		not_special += solve(child, cur, lsp);
	}

	return dp[cur][lsp] = min(special, not_special);
}

int main(){
	int n, root;
	cin >> n >> root;

	adj.resize(n + 1);
	weight.resize(n + 1);

	for (int i = 1; i <= n; i++) cin >> weight[i];

	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].emplace_back(b);
		adj[b].emplace_back(a);
	}

	int ans = weight[root];

	for (int &child : adj[root]) ans += solve(child, root, root);

	printf("%d", ans);
}