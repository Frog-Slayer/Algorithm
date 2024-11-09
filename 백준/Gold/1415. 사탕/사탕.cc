#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

typedef long long ll;

const int MAX = 10000 * 50;
vector<bool> is_prime(MAX + 1, true);

int main() {
	fastio;

	is_prime[0] = is_prime[1] = false;

	for (int i = 2; i * i <= MAX; i++) {
		if (!is_prime[i]) continue;

		for (int j = 2 * i; j <= MAX; j += i) is_prime[j] = false;
	}
	
	int N;
	cin >> N;

	map<int, int> cnt;

	for (int i = 0; i < N; i++){
		int candy;
		cin >> candy;
		cnt[candy]++;
	}

	ll dp[MAX + 1] = {1, 0, };

	for (auto &p: cnt) {
		int candy = p.first, count = p.second;
		if (!candy) continue;

		for (int i = MAX; i >= 0; i--) {
			for (int j = 1; j <= count; j++) {
				int k = i + j * candy;
				if (k > MAX) continue;
				dp[k] += dp[i];
			}
		}
	}

	ll ans = 0;

	for (int i = 2; i <= MAX; i++) if (is_prime[i]) ans += dp[i];

	cout << ans * (cnt[0] + 1);


}