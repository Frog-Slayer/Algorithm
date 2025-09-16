#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

ll gcd(ll a, ll b) { 
	if (!b) return a;
	return gcd(b, a % b);
}

ll extended_euclid(ll A, ll N) { 
	ll a = N, b = A;
	ll s1 = 1, s2 = 0;
	ll t1 = 0, t2 = 1;

    while (a && b){
        ll q = a / b;
        ll r = a % b;

		ll s = s1 - q * s2;
		ll t = t1 - q * t2;

        if (!r) return s2;
		
		a = b;
		b = r;

		s1 = s2;
		s2 = s;

		t1 = t2;
		t2 = t;
	}

	return -1;
}

int main() {
	fastio;

	ll N, A;
	cin >> N >> A;

	ll add_inv = N - A;
	ll mult_inv = extended_euclid(N, A);

	if (gcd(N, A) == 1) {
		if (mult_inv < 0) mult_inv += N;
	} else mult_inv = -1;


	cout << add_inv << ' ' << mult_inv;
}

