#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
typedef long long ll;

int main() { 
	fastio;

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) { 
		ll w, g, h, r;
		cin >> w >> g >> h >> r;

		if (g < h) swap(g, h);
		g -= r;
		h -= r;

		double mmax = sqrt(w * w + (g + h) * (g + h)), mmin = sqrt((g - h) * (g - h) + w * w);

		cout << fixed;
		cout.precision(12);
		cout << mmin << ' ' << mmax << '\n';
	}

}