#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	int N;
	cin >> N;

	map<string, int> m;
    
	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;

		m[s]++;
	}

	string ans = m.begin()->first;
	int M = m.begin()->second;

	for (auto [s, c]: m) {
		if (M < c) {
			M = c;
			ans = s;
		}
		else if (M == c && ans.compare(s) > 0) ans = s; 
	}

	cout << ans;

}
