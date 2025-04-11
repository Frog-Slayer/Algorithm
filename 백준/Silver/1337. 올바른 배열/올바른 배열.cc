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

	vector<int> v(N);
	for (int i = 0; i < N; i++) cin >> v[i];

	sort(all(v));

	int ans = 5;
	for (int i = 0; i < N; i++) {
		int cnt = 0;
		int j = i;

		for (int offset = 0; offset < 5; offset++) {
			if (j >= N) cnt++;
			else if (v[j] == v[i] + offset) j++;
			else cnt++;
		}


		ans = min(ans, cnt);
	}

	cout << ans;
}
