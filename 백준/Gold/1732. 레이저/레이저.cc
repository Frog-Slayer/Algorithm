#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() {
	fastio;

	int N;
	cin >> N;

	vector<tuple<double, ll, int, int, int>> buildings;//angle, dist, height, x, y

	for (int i = 0; i < N; i++) {
		int x, y, z;
		cin >> x >> y >> z;

		double angle = atan2(y, x);
		ll dist = (ll)x * x + (ll)y * y;

		buildings.emplace_back(angle, dist, z, x, y);
	}

	sort(all(buildings));

	vector<pair<int, int>> ans;

	for (int i = 0, j = 0; i < N; i = j) {
		auto &[a1, d1, h1, x1, y1] = buildings[i];
		int max_height = -1;

		while (j < N && get<0>(buildings[j]) == a1){
			auto &[a, d, h, x, y] = buildings[j];
			if (h <= max_height) ans.emplace_back(x, y);
			else max_height = h;
		
			j++;
		}
	}

	sort(all(ans));

	for (auto &[x, y]: ans) cout << x << ' ' << y << '\n';

}
