#include <iostream>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	int n, m, t;
	cin >> n >> m >> t;

	int burger = 0;
	int mincoke = t;

	for (int i = 0; i * n <= t; i++) {
		int bulgogi = (t - (i * n)) / m;

		int coke = t - i * n - bulgogi * m;

		if (coke < mincoke) {
			mincoke = coke;
			burger = i + bulgogi;
		}
		else if (coke == mincoke) burger = max(i + bulgogi, burger);
	}

	cout << burger << ' ' << mincoke;
}