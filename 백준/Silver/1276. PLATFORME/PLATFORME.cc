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

	vector<tuple<int, int, int>> v;

	for (int i = 0; i < N; i++) {
		int y, x1, x2;
		cin >> y >> x1 >> x2;
		v.emplace_back(y, x1, x2);
	}

	sort(all(v));

	int ans = 0;
	vector<int> height(10001);

	for (auto [y, x1, x2] : v) {
		ans += 2 * y - (height[x1] + height[x2 - 1]);

		for (int i = x1; i < x2; i++) height[i] = y;
	}

	cout << ans;
	

}
	
