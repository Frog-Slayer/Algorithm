#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N;
	cin >> N;

	vector<double> sz(N);

	for (int i = 0; i < N; i++) cin >> sz[i];

	sort(all(sz));
	long long ans = 0;

	for (int i = 0; i < N; i++) {
		int lb = lower_bound(all(sz), sz[i] * 0.9) - sz.begin();
		ans += (i- lb);
	}


	cout << ans;
}
