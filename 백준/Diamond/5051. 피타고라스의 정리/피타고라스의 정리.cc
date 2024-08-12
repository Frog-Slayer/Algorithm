#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;

typedef complex<double> cpx;
typedef long long ll;
const double PI = acos(-1);

vector<int> mods_cnt, square_cnt, res;
vector<cpx> a;

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

void mult(vector<cpx> a, vector<cpx> b) {
	int N = 1;
	while (N < a.size() + b.size()) N <<= 1;

	a.resize(N); FFT(a, false);
	b.resize(N); FFT(b, false);

	vector<cpx> c(N);

	for (int i = 0; i < N; i++) c[i] = a[i] * b[i];

	FFT(c, true);

	res.resize(N);

	for (int i = 0; i < N; i++) res[i] = round(c[i].real());
}


int main() {
	int N;
	scanf("%d", &N);

	a.resize(N);
	mods_cnt.resize(N);
	square_cnt.resize(N);

	for (ll i = 1; i < N; i++){
		mods_cnt[(i* i) % N]++;
		square_cnt[(2 * i * i) % N]++;
	}

	for (int i = 0; i < N; i++) a[i] = cpx(mods_cnt[i], 0);

	mult(a, a);

	ll ans = 0;

	for (ll i = 1; i < N; i++) {
		ll j = (i * i) % N;
		ans += (res[j] + res[j + N] - square_cnt[j]) / 2 + square_cnt[j];
	}

	printf("%lld", ans);
}