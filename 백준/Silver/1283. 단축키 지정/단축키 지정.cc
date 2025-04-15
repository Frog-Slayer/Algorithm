#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int to_idx(char c) {
	if ('A' <= c && c <= 'Z') return c -= 'A';
	return c -= 'a';
}

int main() {
	fastio;

	int N;
	cin >> N;
	cin.ignore();

	vector<bool> used(26);

	for (int i = 0; i < N; i++) {
		string s; 
		getline(cin, s);

		int len = s.length();
		int shortcut = -1;

		for (int j = 0; j < len; j++) {
			if (s[j] == ' ') continue;

			if (!j || s[j - 1] == ' ') {
				if (!used[to_idx(s[j])]) {
					shortcut = j;
					break;
				}
			}
 			else if (shortcut < 0 && !used[to_idx(s[j])]) shortcut = j;
		}

		if (shortcut >= 0) used[to_idx(s[shortcut])] = true;

		for (int j = 0; j < len; j++) {
			if (j == shortcut) cout << '[' << s[j] << ']';
			else cout << s[j];
		}

		cout << '\n';

	}

}
