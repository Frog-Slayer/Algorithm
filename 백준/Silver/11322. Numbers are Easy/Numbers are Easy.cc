#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;
	int T;
	cin >> T;

	vector<long long> v;

	for (int i = 0; i < (1 << 19); i++) {
		long long n = 0;
		for (int j = 0; j < 19; j++) {
			n *= 10;
			if (i & (1 << j)) n += 1;
		}
		v.emplace_back(n);
	}
	sort(all(v));

	while (T--) {
		int N;
		cin >> N;

		auto lb = lower_bound(all(v), N);

		while ((*lb % N)) {
			lb = next(lb);
		}

		cout << *lb << '\n';
	}
}

