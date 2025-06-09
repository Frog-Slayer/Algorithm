#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int calc(vector<int> &dice) {
	if (dice[0] == dice[1] && dice[1] == dice[2]) return 10000 + (dice[0] * 1000);
	if (dice[0] == dice[1] || dice[1] == dice[2]) return 1000 +  dice[1] * 100;
	if (dice[0] == dice[2]) return 1000 +  dice[0] * 100;

	return *max_element(all(dice)) * 100;
}

int main() {
	fastio;

	int N;
	cin >> N;

	vector<int> dice(3);
	int ans = 0;
	for (int i = 0; i < N; i++) {

		for (int j = 0; j < 3; j++) cin >> dice[j];

		ans = max(ans, calc(dice));
	}

	cout << ans;
}
