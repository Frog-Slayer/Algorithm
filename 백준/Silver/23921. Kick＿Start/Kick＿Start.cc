#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	int T;
	cin >> T;
	cin.ignore();

	for (int i = 1; i <= T; i++) {
		string s;
		cin >> s;


		int pos = 0;
		int kick = 0;
		int ans = 0;

	  for (size_t i = 0; i + 4 <= s.size(); ++i) {
			if (s.substr(i, 4) == "KICK") {
				kick++;
			} else if (i + 5 <= s.size() && s.substr(i, 5) == "START") {
				ans += kick;
			}
		}


		cout << "Case #" << i << ": " << ans << '\n';

	}

}
