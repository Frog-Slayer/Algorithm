#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int T;
		cin >> T;

		unordered_map<long long, int> m;
		long long ans = 3e9;

		for (int j = 0; j < T; j++) {
			long long n;
			cin >> n;
			m[n]++;
			if (2 * m[n] > T) ans = n;
		}

		if (ans == 3e9) cout << "SYJKGW\n";
		else cout << ans << '\n';
	}


}