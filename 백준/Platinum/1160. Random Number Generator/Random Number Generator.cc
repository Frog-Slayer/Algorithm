#include <iostream>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

typedef long long ll;

struct Matrix {
	__int128 e11, e12, e21, e22;
	ll mod;

	Matrix(ll mod) : mod(mod) {
		e11 = e22 = 1;
		e12 = e21 = 0;
	}

	Matrix operator*(const Matrix &m) {
		Matrix ret(mod);
		ret.e11 = (e11 * m.e11 + e12 * m.e21) % mod;
		ret.e12 = (e11 * m.e12 + e12 * m.e22) % mod;
		ret.e21 = (e21 * m.e11 + e22 * m.e21) % mod;
		ret.e22 = (e21 * m.e12 + e22 * m.e22) % mod;

		return ret; 
	}

	Matrix operator^(ll n) {
		Matrix ret(mod);
		Matrix m(*this);

		while (n) {
			if (n & 1) ret = ret * m;

			m = m * m;
			n >>= 1;
		}

		return ret; 
	}
};

int main() {
	fastio;

	ll m, a, c, x, n, g;
	cin >> m >> a >> c >> x >> n >> g;

	Matrix mat(m);
	mat.e11 = a % m;
	mat.e12 = c % m;

	mat = mat^n;

	ll ans = ((mat.e11 * x + mat.e12) % m) % g;

	cout << ans;

}