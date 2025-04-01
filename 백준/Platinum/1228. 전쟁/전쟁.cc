#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

typedef struct {
	int cost;
	int sz;
	vector<int> sub;
} country;

const int INF = 1e9;
int N, M;
unordered_map<string, int> um;
vector<int> indegree;
vector<country> countries;
vector<vector<int>> dp;

void solve(int cur) {
	dp[cur][0] = 0;

	for (auto &child : countries[cur].sub) {
		solve(child);
		for (int i = M; i; i--) {
			for (int j = 0; j <= i; j++) {
				dp[cur][i] = min(dp[cur][i], dp[child][j] + dp[cur][i - j]);
			}
		}
	}

	for (int i = 0; i <= countries[cur].sz; i++) dp[cur][i] = min(dp[cur][i], countries[cur].cost);
}

int dfs(int cur) {
	int sz = 1;

	for (auto &child : countries[cur].sub) sz += dfs(child);

	return countries[cur].sz = sz;
}

int main() {
	fastio;

	cin >> N >> M;

	countries.resize(N + 1);
	indegree.resize(N + 1);
	dp.resize(N + 1, vector<int>(N + 1, INF));

	cin.ignore();

	int idx = 0;
	
	for (int i = 0; i < N; i++) {
		string line;
		getline(cin, line);

		vector<string> words;
		istringstream iss(line);
		string word;

		while (iss >> word) words.push_back(word);

		for (int i = 0; i < words.size(); i++) {
			if (!i) {
				if (um.find(words[i]) == um.end()) um[words[i]] = ++idx;
			}
			else if (i == 1) countries[um[words[0]]].cost = stoi(words[i]);
			else {
				if (um.find(words[i]) == um.end()) um[words[i]] = ++idx;
				int child = um[words[i]];
				countries[um[words[0]]].sub.emplace_back(child);
				indegree[child]++;
			}
		}
	}

	for (int i = 1; i <= N; i++) if (!indegree[i]) countries[0].sub.emplace_back(i);
	countries[0].cost = INF;

	dfs(0);
	solve(0);

	cout << dp[0][M];
}
