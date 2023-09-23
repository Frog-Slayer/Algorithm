#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
#define ll long long

long long N;
int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
map<ll, ll> factor;

long long int mult(long long int p,long long int q, long long int m)
{
    p %= m;
    q %= m;
    long long int r = 0;
    long long int w = p;
    while(q)
    {
        if(q%2)
        {
            r = (r+w)%m;
        }
        w=(w+w)%m;
        q>>=1;
    }
    return r;
}

ll gcd(ll a, ll b){
	ll r;
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (a < b) swap(a, b);
	while (a && b){
		r = a % b;
		if (!r) return b;
		a = b;
		b = r;
	}
	return a + b;
}

ll pow_mod(ll a, ll k, ll p){
	ll ret = 1;
	a %= p;
	while (k){
		if (k % 2) ret = mult(ret, a, p);
		k /= 2;
		a = mult(a, a, p); 
	}
	return ret;
}

bool millerRabin(ll n, ll p){
	if (n % p == 0) return false;
	ll k = n - 1; // k can be expressed as 2^h * m (m is odd)
	while (true){
		ll d = pow_mod(p, k, n);
		if (d == n - 1) return true;
		if (k % 2) return (d == 1 || d == n - 1);
		k /= 2;
	}
}

bool isPrime(ll n){
	if (n == 1) return false;

	for (int i = 0; i < 13; i++){
		if (n == prime[i]) return true;
		if (n % prime[i] == 0) return false;
		if (!millerRabin(n, prime[i])) return false;
	}
	return true;
}

ll polynom(ll x, ll a, ll p){
	return (mult(x, x, p) + a) % p;
}

ll pollardRho(long long n){
	if (isPrime(n)) return n;
	if (n % 2 == 0) return 2;
	ll a = rand() % (n - 2) + 2;
	ll x0 = rand() % 20 + 1;
	ll d = 1;
	ll xj = x0, xk = x0;
	while (d == 1){
		xj = polynom(xj, a, n);
		xk = polynom(polynom(xk, a, n), a, n);
		d = gcd(xk - xj, n);
	}
	return pollardRho(d);
}

int main(){
	scanf("%lld", &N);
	long long org = N;
	while (N != 1){
		ll nonTrivialDivisor = pollardRho(N);
        while (N % nonTrivialDivisor == 0){
            N /= (long long)nonTrivialDivisor;
            factor[nonTrivialDivisor]++;
		}

	}

    int ans = 1;
	for (auto f : factor){
        if (f.second % 2) {
            ans = 2;
            break;
        }
	}
    if (ans == 2){
        for (auto f : factor){
            if (f.first % 4 == 3 && f.second % 2) {
                ans = 3;
            }
        }
    }
    if (ans == 3){
        while (org % 4 == 0) {
            org /= 4;
        }
        if (org % 8 == 7) ans = 4;
    }


	printf("%d", ans);
}