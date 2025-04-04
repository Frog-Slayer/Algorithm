#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

const int MAX_N = 50;

int main() {
	fastio;

	string s;
	cin >> s;

	int len = s.length();

	vector<vector<bool>> dp(len, vector<bool>(len));

	for (int i = 0; i < len; i++) dp[i][i] = 1;
	for (int i = 0; i < len - 1; i++) dp[i][i + 1] = (s[i] == s[i + 1]);

	for (int i = 3; i <= len; i++) {
		for (int j = 0; j < len; j++) {
			if (j + i > len) continue;
			if (s[j] == s[j + i - 1] && dp[j + 1][j + i - 2]) dp[j][j + i - 1] = 1;
		}
	}

	vector<int> ans(len, 2501);

	for (int i = 0; i < len; i++) {
		for (int j = 0; j <= i; j++) {
			if (dp[j][i]) ans[i] = j ? min(ans[i], ans[j - 1] + 1) : 1;
		}
	}


	cout << ans[len - 1];

}
