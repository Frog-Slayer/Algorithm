#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;
const int INF = 10000000;

struct Task { 
	int w, t, p;
};

int dp[1001][100001];

int main() { 
	fastio;

	int N, S;
	cin >> N >> S;

	vector<Task> tasks(N + 1);
	vector<int> next(N + 1);
	vector<vector<int>> grp;

	for (int i = 1; i <= N; i++) cin >> tasks[i].w;
	for (int i = 1; i <= N; i++) cin >> tasks[i].t;
	for (int i = 1; i <= N; i++) {  
		int p;
		cin >> p;
		tasks[i].p = p;
		if (p) next[p] = i;
	}


	for (int i = 1; i <= N; i++) { 
		if (!tasks[i].p) { 
			int j = i;
			grp.emplace_back();

			while (true) { 
				grp.back().emplace_back(j);
				if (!next[j]) break;
				tasks[next[j]].w += tasks[j].w;
				tasks[next[j]].t += tasks[j].t;
				j = next[j];
			}
		}
	}

	int ans = INF;

	for (int i = 1; i <= 100000; i++) dp[0][i] = INF;

	for (int j = 0; j < grp[0].size(); j++) { 
		auto [w, t, p] = tasks[grp[0][j]];
		dp[0][w] = t;
		if (w >= S) ans = min(ans, t);
	}

	for (int i = 1; i < grp.size(); i++) { 
		for (int s = 0; s <= 100000; s++) dp[i][s] = dp[i - 1][s];

		for (int j = 0; j < grp[i].size(); j++) { 
			auto [w, t, p] = tasks[grp[i][j]];

			for (int s = 0; s <= 100000; s++) { 
				if (s - w >= 0) dp[i][s] = min(dp[i][s], dp[i - 1][s - w] + t);
				if (s >= S && dp[i][s] < INF) ans = min(ans, dp[i][s]);
			}
		}
	}


	if (ans == INF) cout << -1;
	else cout << ans;
}
