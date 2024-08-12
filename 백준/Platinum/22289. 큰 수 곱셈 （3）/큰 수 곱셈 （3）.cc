#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <string.h>
using namespace std;

typedef complex<double> cpx;
const int MAX_LEN = 1000000;
const double PI = acos(-1);
char A[MAX_LEN + 1], B[MAX_LEN + 1];

vector<cpx> a, b;
int len_a = strlen(A), len_b = strlen(B);

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


vector<int> mult(vector<cpx> &a, vector<cpx> &b) {
	int N = 1;
	while (N < a.size() + b.size()) N <<= 1;

	a.resize(N); FFT(a, false);
	b.resize(N); FFT(b, false);

	vector<cpx> c(N);

	for (int i = 0; i < N; i++) {
		c[i] = a[i] * b[i];
	}

	FFT(c, true);
	vector<int> res(N);

	for (int i = 0; i < N; i++) res[i] = round(c[i].real());

	return res;
}


int main() {
	scanf("%s %s", A, B);
	
	if (A[0] == '0' || B[0] == '0') {
		printf("0");
		return 0;
	}

	len_a = strlen(A), len_b = strlen(B);
	
	for (int i = len_a - 1; i >= 0; i--) a.emplace_back(A[i] - '0', 0);

	for (int i = len_b - 1; i >= 0; i--) b.emplace_back(B[i] - '0', 0);

	vector<int> res = mult(a, b);

	int N = res.size();

	for (int i = 0; i < N - 1; i++) {
		res[i + 1] += res[i] / 10;
		res[i] %= 10;
	}

	bool is_leading_zero = true;

	for (int i = N - 1; i >= 0; i--) {
		if (res[i]) is_leading_zero = false;

		if (!is_leading_zero) printf("%d", res[i]);
	}
}