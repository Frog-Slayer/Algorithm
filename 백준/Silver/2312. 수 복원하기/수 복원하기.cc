#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	vector<bool> is_prime(100001, true);
	is_prime[0] = is_prime[1] = false;

	for (int i = 2; i * i <= 100000; i++) {
		if (!is_prime[i]) continue;
		for (int j = 2 * i; j <= 100000; j += i) is_prime[j] = false;
	}

	vector<int> primes;
	for (int i = 2; i <= 100000; i++) if (is_prime[i]) primes.emplace_back(i);

	int T;
	cin >> T;

	while (T--) {
		int N;
		cin >> N;
		
		map<int, int> cnt;

		for (auto &prime : primes) {
			if (N == 1) break;
			while (N % prime == 0) {
				cnt[prime]++;
				N /= prime;
			}
		}

		for (auto pr : cnt) cout << pr.first << ' ' << pr.second << '\n';
	}
	
}