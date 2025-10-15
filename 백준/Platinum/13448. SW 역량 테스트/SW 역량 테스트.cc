#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

struct Problem { 
	ll m, p, r;

	bool operator<(const Problem &o) { 
		return r * o.p < o.r * p;
	}

};

ll dp[51][100001];

int main() { 
	fastio;

	int N, T;
	cin >> N >> T;

	vector<Problem> problems(N + 1);

	for (int i = 1; i <= N; i++) cin >> problems[i].m;
	for (int i = 1; i <= N; i++) cin >> problems[i].p;
	for (int i = 1; i <= N; i++) cin >> problems[i].r;

	sort(problems.begin() + 1, problems.end());

	for (int i = 1; i <= N; i++) for (int j = 0; j <= T; j++) dp[i][j] = -1;

	auto solve = [&](auto self, int cur, int t) -> ll { 
		if (cur > N) return 0;

		auto &ret = dp[cur][t];
		if (ret >= 0) return ret;

		ret = self(self, cur + 1, t);

		auto [m, p, r] = problems[cur];
		int nt = t + r;
		if (nt <= T) { 
			ret = max(ret, self(self, cur + 1, nt) + m - nt * p);
		}

		return ret;
	};


	ll ans = solve(solve, 1, 0);
	cout << ans;
}
