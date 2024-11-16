#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int gcd(int a, int b){ 
	if (a < 0) a *= -1;
	if (b < 0) b *= -1;

	if (a < b) swap(a, b);
	int r;

	while (b) {
		r = a % b;
		a = b;
		b = r;
	}

	return a;

}


int main() {
	fastio;
	int xs, ys;
	cin >> xs >> ys;

	int xe, ye, dx, dy;
	cin >> xe >> ye >> dx >> dy;

	int g = gcd(dx, dy);
	dx /= g;
	dy /= g;

	int dist = (xs - xe) * (xs - xe) + (ys - ye) * (ys - ye);

	for (int i = 0; ; i++) {
		int nx = xe + dx;
		int ny = ye + dy;

		int d = (xs - nx) * (xs - nx) + (ys - ny) * (ys - ny);
		if (d >= dist) break;
		dist = d;
		xe = nx, ye = ny;
	}

	cout << xe << ' ' << ye;

}