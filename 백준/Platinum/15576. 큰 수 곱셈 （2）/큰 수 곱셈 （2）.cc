#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <string.h>
using namespace std;

typedef complex<double> cpx;
const int MAX_LEN = 300000;
const double PI = acos(-1);
char A[MAX_LEN + 1], B[MAX_LEN + 1];

vector<cpx> a, b;
int len_a = strlen(A), len_b = strlen(B);

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

vector<int> mult(vector<cpx> &a, vector<cpx> &b) {
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
	vector<int> res(N);

	for (int i = 0; i < N; i++) res[i] = round(c[i].real() / N);

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