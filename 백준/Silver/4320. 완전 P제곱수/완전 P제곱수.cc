#include <iostream>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

typedef long long ll;

int main() {
	fastio;

	while (true) {
		long long N;
		cin >> N;

		if (!N) break;
		int sign = N > 0 ? 1 : -1;
		N *= sign;
		
		int ans = 1;

		for (ll i = 2; i * i <= N; i++) {
			ll m = 1, n = N;
			int count = 0;

			while (n != 1 && n % i == 0){
				n /= i;
				count++;
			}

			if (n != 1 || (sign < 0 && count % 2 == 0)) continue;
			ans = count;
			break;
		}
		cout << ans << '\n';
	}
}