#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

int N;
vector<int> S;
set<int> ss;
vector<pair<long long, int>> ans;

bool compare(pair<long long, int> &p, pair<long long, int> &q) {
	if (p.first == q.first) return p.second < q.second;
	if (p.first < 0) return false;
	if (q.first < 0) return true;
	return p.first < q.first;
}

int main(){
	scanf("%d", &N);
	S.resize(N + 1);

	for (int i = 1; i <= N; i++) scanf("%d", &S[i]);

	sort(S.begin() + 1, S.end());

	int n;
	scanf("%d", &n);

	for (int i = 0; i <= N; i++) {
		if (i) ans.emplace_back(0, S[i]);
		ss.insert(S[i]);

		for (int j = 1; j <= n; j++) {
			long long cur = S[i] - j;

			if (cur <= 0) continue;
			if (i && cur == S[i - 1]) break;
			if (ss.count(cur)) break;
			ss.insert(cur);

			ans.emplace_back((cur - S[i - 1]) * (S[i] - cur) - 1, cur); 
		}

		for (int j = 1; j <= n; j++) {
			long long cur = S[i] + j;
			if (i != N && cur == S[i + 1]) break;
			if (ss.count(cur)) break;
			ss.insert(cur);

			if (i != N) ans.emplace_back((cur - S[i]) * (S[i + 1] - cur) - 1, cur);
			else ans.emplace_back(-1, cur);
		}
	}

	sort(ans.begin(), ans.end(), compare);

	for (int i = 0; i < n; i++) printf("%d ", ans[i].second);
}