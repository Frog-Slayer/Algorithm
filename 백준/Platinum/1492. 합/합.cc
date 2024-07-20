#include <iostream>
using namespace std;

typedef long long ll;

const int MOD = 1000000007;
int N, K;
ll comb[52][52];
ll dp[51];

ll pow_mod(ll a, ll k) {//a^k
	ll ret = 1;

	while (k) {
		if (k & 1) { 
			ret *= a;
			ret %= MOD;
		}
		a *= a;
		a %= MOD;
		k >>= 1;
	}

	return ret;
}

ll solve(int k){
	ll &ret = dp[k];

	if (ret) return ret;

	ret = pow_mod(N + 1, k + 1) - 1;

	for (int i = 0; i < k; i++) {
		ll t = comb[k + 1][i] * solve(i);
		t %= MOD;

		ret -= t;
		ret %= MOD;
	}

	ret *= pow_mod(comb[k + 1][k], MOD - 2);
	ret %= MOD;

	if (ret < 0) ret = (ret + MOD) % MOD;

	return ret;
}

void set_comb(){
	for (int i = 0; i < 52; i++) {
		for (int j = 0; j < 52; j++) {
			if (i == j || j == 0) comb[i][j] = 1;
			else if (j > i) break;
			else {
				comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
				comb[i][j] %= MOD;
			}
		}
	}
}

int main(){
	set_comb();

	scanf("%d%d", &N, &K);

	printf("%lld", solve(K));
}