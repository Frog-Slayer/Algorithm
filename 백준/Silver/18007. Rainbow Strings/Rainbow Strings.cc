#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() {
	fastio;

	string s;
	cin >> s;

	int cnt[26] = {0, };

	for (char c: s) cnt[c - 'a']++;

	ll ans = 1;
	int mod = 11092019;

	for (int i = 0; i < 26; i++) { 
		ans *= (cnt[i] + 1);
		ans %= mod;
	}

	cout << ans;
}
