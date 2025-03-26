#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	string s, t, u;

	cin >> s >> t >> u;

	vector<vector<vector<int>>> LCS(s.length() + 1, vector<vector<int>>(t.length() + 1, vector<int>(u.length() + 1)));

	for (int i = 0; i < s.length(); i++) {
		for (int j = 0; j < t.length(); j++) {
			for (int k = 0; k < u.length(); k++) {
				if (s[i] == t[j] && t[j] == u[k]) LCS[i + 1][j + 1][k + 1] = LCS[i][j][k] + 1;
				else LCS[i + 1][j + 1][k + 1] = max({LCS[i][j + 1][k + 1] , LCS[i + 1][j][k + 1], LCS[i + 1][j + 1][k]});
			}
		}
	}

	cout << LCS[s.length()][t.length()][u.length()];
}
