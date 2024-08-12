#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;

typedef complex<double> cpx;
const double PI = acos(-1);
const int MAX_N = 1000000;

vector<bool> is_not_prime(MAX_N +1);
vector<int> primes, res;
vector<cpx> odd_prime_coeff(MAX_N + 1), semi_prime_coeff(MAX_N + 1);

void FFT(vector<cpx> &a, bool inv) {
	int N = a.size();

    for(int i = 0; i < N; i++) {
        int rev = 0;
        for(int j = 1, k = i; j < N; j <<= 1, k >>= 1) rev = (rev << 1) + (k & 1);
        if(i < rev) swap(a[i], a[rev]);
    }

    for(int len = 2; len <= N; len <<= 1) {
        double x = 2 * PI / len * (inv ? -1 : 1);
        cpx omega_n(cos(x), sin(x));

        for(int i = 0; i < N; i += len) {
            cpx omega(1, 0);
            for(int j = 0; j < len/2; j++) {
                int cur = i + j;
                cpx even = a[cur];
                cpx odd = a[cur + len/2] * omega;
                a[cur] = even + odd;
                a[cur + len/2] = even - odd;
                omega *= omega_n;
            }
        }
    }
    if (inv) for(int i = 0; i < N; i++) a[i] /= N;
}

void multiply(vector<cpx> &a, vector<cpx> &b) {
	int N = 1;
	while (N < a.size() + b.size()) N <<= 1;

	a.resize(N);
	b.resize(N);

	FFT(a, false);
	FFT(b, false);

	vector<cpx> c(N);

	for (int i = 0; i < N; i++) {
		c[i] = a[i] * b[i];
	}

	FFT(c, true);
	res.resize(N);
	
	for (int i = 0; i < N; i++) res[i] = round(c[i].real());
}

void init(){

	for (int i = 2; i <= MAX_N; i++) {
		if (is_not_prime[i]) continue;
		primes.emplace_back(i);
		for (int j = 2 * i; j <= MAX_N; j += i) {
			is_not_prime[j] = true;
		}
	}

	for (int &p : primes) {
		if (p != 2) odd_prime_coeff[p] = cpx(1, 0);
		if (p * 2 <= MAX_N) semi_prime_coeff[p * 2] = cpx(1, 0);
	}

	multiply(odd_prime_coeff, semi_prime_coeff);
}

int main() {
	int T;
	scanf("%d", &T);
	
	init();

	while (T--) {
		int N;
		scanf("%d", &N);
		printf("%d\n", res[N]);
	}
}