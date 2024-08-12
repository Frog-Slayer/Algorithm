#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;

typedef complex<double> cpx;
const double PI = acos(-1);
const int MAX_N = 60000;

vector<cpx>	upper(MAX_N + 1), lower(MAX_N + 1);
vector<int> middle, res;

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
	
	for (int i = 0; i < N; i++){
		res[i] = round(c[i].real());
	}
}

int main() {
	int nu, nm, nl;
	scanf("%d", &nu);

	for (int x, i = 0; i < nu; i++) {
		scanf("%d", &x);
		upper[x + 30000] = cpx(1, 0);
	}

	scanf("%d", &nm);
	for (int x, i = 0; i < nm; i++) {
		scanf("%d", &x);
		middle.emplace_back(x + 30000);
	}

	scanf("%d", &nl);
	for (int x, i = 0; i < nl; i++) {
		scanf("%d", &x);
		lower[x + 30000] = cpx(1, 0);
	}

	multiply(upper, lower);

	int ans = 0;

	for (int &x : middle) {
		ans += res[x * 2];
	}

	printf("%d", ans);
}