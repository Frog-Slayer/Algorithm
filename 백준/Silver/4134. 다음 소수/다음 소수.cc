#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

typedef long long ll;

bool is_prime(ll n) {
	if (!n || n == 1 || (n != 2 && n % 2 == 0)) return false;

	for (ll i = 3; i * i <= n; i += 2) if (n % i == 0) return false;

	return true;
}

int main()  {
	fastio;
	
	int T;
	cin >> T;

	while (T--){
		ll n;
		cin >> n;

		while (!is_prime(n)) n++;
	
		cout << n << '\n';
	}
}
