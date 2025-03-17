#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int T;
	cin >> T;
	cin.ignore();

	while (T--) {
		string s;
		getline(cin, s);

		int len = s.length();
		int height = 0, max_height = 0;

		for (int i = 0; i < len; i++) {
			if (s[i] == '[') height += 1;
			else height -= 1;

			max_height = max(max_height, height);
		}
	
		cout << (1 << max_height) << '\n';
	}
}
