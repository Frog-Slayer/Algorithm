#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int W, H, X, Y, P;
	cin >> W >> H >> X >> Y >> P;

	int radius = H / 2;

	pair<int, int> left_center = {X, Y + radius};
	pair<int, int> right_center = {X + W, Y + radius};

	auto is_in = [&](int x, int y) -> bool {
		if (X <= x && x <= X + W && Y <= y && y <= Y + H) return true;
		auto &[lx, ly] = left_center;
		auto &[rx, ry] = right_center;

		return ((lx - x) * (lx - x) + (ly - y) * (ly - y) <= radius * radius) ||
			   ((rx - x) * (rx - x) + (ry - y) * (ry - y) <= radius * radius);
	};

	int ans = 0;

	for (int i = 0; i < P; i++ ) {
		int x, y;
		cin >> x >> y;

		ans += is_in(x, y);
	}

	cout << ans;

}
