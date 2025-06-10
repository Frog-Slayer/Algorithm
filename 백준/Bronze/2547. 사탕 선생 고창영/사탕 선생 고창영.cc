#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() {
	fastio;

	int T;
	cin >> T;

	while (T--) {
		int N;
		cin >> N;

		int sum = 0;
		for (int i = 0; i < N; i++) {
			ll candy;
			cin >> candy;

			sum += (candy % N);
			sum %= N;
		}

		if (!sum) cout << "YES\n";
		else cout << "NO\n";
	}
}
