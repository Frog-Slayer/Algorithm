#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() {
	fastio;

	int N, T;
	cin >> N >> T;

	vector<int> L(N), R(N);
	for (int i = 0; i < N; i++) cin >> L[i] >> R[i];

	int l = 0, r = T;
	int ans = -1;

	while (l < r) {
		int S = (l + r) / 2;
		int min_sum = 0, max_sum = 0;

		bool is_possible = true;

		for (int i = 0; i < N; i++) {
			if (S < L[i]) {
				is_possible = false;
				break;
			}

			min_sum += L[i];
			max_sum += min(S, R[i]);
		}

		if (!is_possible || T < min_sum || max_sum < T) l = S + 1;
		else ans = r = S;
	}

	cout << ans;
}
