#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N, Q;

	cin >> N >> Q;

	vector<long long> v(N + 1);

	for (int i = 1; i <= N; i++) {
		cin >> v[i];

		if (i) v[i] += v[i - 1];
	}

	for (int i = 0; i < Q; i++) {
		long long T;
		cin >> T;

		cout << lower_bound(all(v), T + 1) - v.begin() << '\n';
	}
}
