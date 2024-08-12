#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
using namespace std;

typedef complex<double> cpx;
const double PI = acos(-1);
const int MAX_N = 1e5;
char RPS_machine[MAX_N + 1], my_machine[MAX_N + 1];

vector<cpx> r1, r2, r3;
vector<cpx> m1, m2, m3; 
vector<cpx> c1, c2, c3;

void FFT(vector<cpx> &a, bool inv) {
	int N = a.size();

    for(int i = 0; i < N; i++) {
        int rev = 0;
        for(int j = 1, k = i; j < N; j <<= 1, k >>= 1) rev = (rev << 1) + (k & 1);
        if (i < rev) swap(a[i], a[rev]);
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

void mult(vector<cpx> &a, vector<cpx> &b, vector<cpx> &c) {
	int N = 1;
	while (N < a.size() + b.size()) N <<= 1;

	a.resize(N); FFT(a, false);
	b.resize(N); FFT(b, false);
	c.resize(N);

	for (int i = 0; i < N; i++) c[i] = a[i] * b[i];

	FFT(c, true);
}


int main() {
	int N, M;
	scanf("%d%d", &N, &M);

	scanf("%s", RPS_machine);

	r1.resize(N);
	r2.resize(N);
	r3.resize(N);

	for (int i = 0; i < N; i++) {
		switch (RPS_machine[i]) {
			case 'R': r1[i] = cpx(1, 0); break;
			case 'P': r2[i] = cpx(1, 0); break;
			case 'S': r3[i] = cpx(1, 0); break;
		}
	}

	m1.resize(M);
	m2.resize(M);
	m3.resize(M);

	scanf("%s", my_machine);

	reverse(my_machine, my_machine + M);

	for (int i = 0; i < M; i++) {
		switch (my_machine[i]) {
			case 'P': m1[i] = cpx(1, 0); break;
			case 'S': m2[i] = cpx(1, 0); break;
			case 'R': m3[i] = cpx(1, 0); break;
		}
	}

	mult(r1, m1, c1);
	mult(r2, m2, c2);
	mult(r3, m3, c3);

	int ans = 0;

	for (int i = M - 1; i < M + N - 1; i++) {
		ans = max(ans, (int)(round(c1[i].real()) + round(c2[i].real()) + round(c3[i].real())));
	}

	printf("%d", ans);
}