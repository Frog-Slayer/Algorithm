#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

const int INF = 10000;

int cost(string s, string t) {
	int cnts[26] = {0, }, cntt[26] = {0, };
	int len = s.length();

	for (int i = 0; i < len; i++) cnts[s[i] - 'a']++, cntt[t[i] - 'a']++;
	for (int i = 0; i < 26; i++) if (cnts[i] != cntt[i]) return -1;

	int ret = 0;

	for (int i = 0; i < len; i++) ret += (s[i] != t[i]);

	return ret;
	
}

int main() {
	fastio;

	string s;
	cin >> s;

	int len = s.length();

	int N;
	cin >> N;

	vector<string> words(N);
	vector<int> dp(len, INF);

	for (int i = 0; i < N; i++) cin >> words[i];

	for (int i = 0; i < len; i++) {
		int curmin = 0;
		if (i) curmin = dp[i - 1];

		for (int j = 0; j < N; j++) {
			int jlen = words[j].length();

			if (i + jlen > len) continue;

			int c = cost(s.substr(i, jlen), words[j]);
			if (c < 0) continue;

			dp[i + jlen - 1] = min(dp[i + jlen - 1], curmin + c);
		}
	}


	cout << (dp[len - 1] == INF ? -1 : dp[len - 1]);

}
