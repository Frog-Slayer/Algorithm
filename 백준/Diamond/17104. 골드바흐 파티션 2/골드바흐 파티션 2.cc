#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;

typedef complex<double> cpx;
const double PI = acos(-1);
const int MAX_N = 500000;

vector<int> res;
vector<bool> is_prime(2 * MAX_N + 1 , 1);
vector<cpx> primes_coeff(MAX_N + 1), cp(MAX_N + 1);

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

	for (int i = 0; i < N; i++) c[i] = a[i] * b[i];

	FFT(c, true);

	res.resize(N);
	
	for (int i = 0; i < N; i++) res[i] = round(c[i].real());
}

void init() {
	is_prime[0] = is_prime[1] = false;
	
	for (int i = 2; i <= 2 * MAX_N; i++) {
		if (!is_prime[i]) continue;
		if (i & 1) {
			primes_coeff[(i - 1) / 2] = cpx(1, 0);
			cp[(i - 1) / 2] = cpx(1,0);
		}

		for (int j = 2 * i; j <= 2 * MAX_N; j += i) is_prime[j] = false;
	}

	multiply(primes_coeff, cp);
}

int main() {
	init();

	int T;
	scanf("%d", &T);

	while (T--) {
		int N;
		scanf("%d", &N);
        if (N == 4) printf("1\n");
		else printf("%d\n", (res[N / 2 - 1] + 1) / 2);
	}
}