#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

typedef complex<double> cpx;
const int MAX = 200000;
const double PI = acos(-1);

vector<cpx> k(MAX + 1);

void FFT(vector<cpx> &a, cpx omega_n) {
	int N = a.size();
	if (a.size() == 1) return;

	vector<cpx> even(N / 2), odd(N / 2);

	for (int i = 0; i < N; i++) {
		if (i & 1) odd[i / 2] = a[i];
		else even[i / 2] = a[i];
	}

	FFT(even, omega_n * omega_n);
	FFT(odd, omega_n * omega_n);

	cpx omega(1, 0);

	for (int i = 0; i < N / 2; i++) {
		a[i] = even[i] + omega * odd[i];
		a[i + N / 2] = even[i] - omega * odd[i];
		omega *= omega_n;
	}
}

vector<int> mult(vector<cpx> a, vector<cpx> b) {
	int N = 1;
	while (N < a.size() + b.size()) N <<= 1;
	
	double angle = 2 * PI / N;
	cpx omega_n = cpx(cos(angle), sin(angle));

	a.resize(N); FFT(a, omega_n);
	b.resize(N); FFT(b, omega_n);

	vector<cpx> c(N);

	for (int i = 0; i < N; i++) {
		c[i] = a[i] * b[i];
	}

	omega_n = cpx(cos(-angle), sin(-angle));
	FFT(c, omega_n);

	vector<int> ret(N);

	for (int i = 0; i < N; i++){
		ret[i] = round(c[i].real()) / N;
	}

	return ret;
}


int main() {
	int N, M;
	scanf("%d", &N);

	k[0] = cpx(1, 0);

	for (int i = 0; i < N; i++) {
		int ki;
		scanf("%d", &ki);
		k[ki] = cpx(1, 0);
	}

	vector<int> res = mult(k, k);

	int ans = 0;

	scanf("%d", &M);

	for (int i = 0; i < M; i++) {
		int di;
		scanf("%d", &di);
		if (res[di]) ans++;
	}

	printf("%d", ans);
}