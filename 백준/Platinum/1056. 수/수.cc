#include <iostream>
#include <map>
#include <algorithm>
#include <math.h>
using namespace std;

typedef long long ll;
ll N;
int limit[61];
map<ll, ll> m;

void set_limit(int k){//a^k <= 1e18이 되는 최대 a
	int low = 0, high = 1e9;

	while (low <= high) {
		int mid = (low + high) / 2;
		double ln = log(mid) * k;

		if (ln < 18 * log(10)) low = mid + 1;
		else high = mid - 1; 
	}

	limit[k] = low - 1;
}

ll power(ll n, int k) {//n^k
	ll ret = 1;

	while (k) {
		if (k & 1) {
			ret *= n;
		}
		n *= n;
		k >>= 1;
	}

	return ret;
}

int bin_search(ll n, int k) {
	int low = 0, high = limit[k];

	while (low <= high) {
		int mid = (low + high) / 2;
		ll pow = power(mid, k);
		//printf("%d^%d = %lld\n", mid, k, pow);

		if (pow < n) low = mid + 1;
		else high = mid - 1;
	}

	return low;
}

ll dp(ll n){
	if (m.find(n) != m.end()) return m[n];

	m[n] = n - 1;

	for (int i = 2; i < 61; i++) {
		int bs = bin_search(n, i);
		//printf("bs: %d\n", bs);
	
		m[n] = min({m[n], dp(bs) + llabs(power(bs, i) - n) + 1, dp(bs - 1) + llabs(power(bs - 1, i) - n) + 1});
	}

	return m[n];
}

int main(){
	scanf("%lld", &N);

	for (int i = 2; i < 61; i++) set_limit(i);

	printf("%lld", dp(N));
}