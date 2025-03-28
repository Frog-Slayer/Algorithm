#include <iostream>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

typedef __float128 lf;
typedef long long ll;
typedef long double ld;

const lf pi = 3.1415926535897932384626433832795028841971693993751058209749445923Q;

//sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...
lf sin(lf x) {
	x -= ll(x / (2 * pi)) * 2 * pi;

	lf ret = 0;
	lf term = x;
	int sign = 1;

	for (int i = 1; i < 30; i += 2) {
		ret += sign * term; 
		sign *= -1;
		term *= x * x / ((i + 1) * (i + 2));
	}

	return ret;
}

ld round(lf x) {
	ll lx = x * 1e6 + 0.5;
	return lx / 1e6;
}


int main() {
	fastio;

	int a, b, c;
	cin >> a >> b >> c;

	lf A = a, B = b, C = c;
	lf left = (C - B)/A, right = (C + B)/A, x;

	int T = 100;

	while (T--) {
		x = (left + right) / 2;
		lf eval = A * x + B * sin(x);
		if (eval < C)  left = x;
		else right = x;
	}

	cout << fixed;
	cout.precision(6);

	cout << round(x);
}
