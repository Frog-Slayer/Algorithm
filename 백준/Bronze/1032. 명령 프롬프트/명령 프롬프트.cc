#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;
	
	int N;
	cin >> N;

	string ans = "";
	string prev = "";

	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;

		if (prev.empty()) {
			ans = prev = s;
		}

		int len = s.length();

		for (int j = 0; j < len; j++) {
			if (s[j] == prev[j]) continue;
			else ans[j] = '?';
		}

		prev = s;
	}

	cout << ans;
}

