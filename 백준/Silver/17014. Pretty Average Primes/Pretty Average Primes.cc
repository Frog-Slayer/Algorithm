#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

vector<bool> is_prime(2000001, true);
vector<int> primes;

void set_prime() { 
	for (int i = 2; i * i < 2000001; i++) { 
		if (!is_prime[i]) continue;
		for (int j = 2 * i; j < 2000001; j += i) is_prime[j] = false;
	}

	for (int i = 2; i < 2000001; i++) if (is_prime[i]) primes.emplace_back(i);
}

int main() {
	fastio;

	int T;
	cin >> T;

	set_prime();

	while (T--) { 
		int N;
		cin >> N;

		N *= 2;

		for (int prime: primes) { 
			if (binary_search(all(primes), N - prime)) { 
				cout << prime << ' ' << N - prime << '\n';
				break;
			}
		}
	}
}

