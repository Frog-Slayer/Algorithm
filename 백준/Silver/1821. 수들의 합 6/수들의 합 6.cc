#include <iostream>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N, F;
	cin >> N >> F;

	vector<int> v(N);

	for (int i = 0; i < N; i++) v[i] = i + 1;

	do {
		vector<int> sum(v);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N - i - 1; j++) {
				sum[j] = sum[j] + sum[j + 1];
			}
		}

		if (sum[0] == F) {
			for (int &n : v) cout << n << ' ';
			return 0;
		}

	} while(next_permutation(all(v)));
}
