#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef __int128 ll;

ll comb[101][101];

int main() {
	fastio;

	for (int i = 0; i < 101; i++) {
		comb[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
		}
	}

	int n, m;
	cin >> n >> m;

	ll ans = comb[n][m];
	string s;

	while (ans) {
		s += (ans % 10) + '0';
		ans /= 10;
	}

	reverse(all(s));

	cout << s;
}