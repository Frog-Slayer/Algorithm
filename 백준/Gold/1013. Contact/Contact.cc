#include <iostream>
#include <vector>
#include <regex>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

enum FLAG{ 
	none,
	_100,
	_1_AFTER_100,
	_01
};

int main() { 
	fastio;

	int T;
	cin >> T;

	while (T--) { 
		string s;
		cin >> s;

		regex patt("(100+1+|01)+");

		bool yes = regex_match(s, patt);

		cout << (yes ? "YES\n" : "NO\n");

	}

}
