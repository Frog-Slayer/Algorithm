
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define all(v) v.begin(), v.end()

typedef long long ll;
typedef pair<ll ,ll> Point;
int N;

Point operator+(Point &p1, Point &p2) { return Point(p1.first + p2.first, p1.second + p2.second); }
Point operator-(Point &p1, Point &p2) { return Point(p1.first - p2.first, p1.second - p2.second); }
ll operator*(Point &p1, Point &p2) { return p1.first * p2.second - p1.second * p2.first; }

vector<tuple<int, int, int>> deposits;

int solve(int x, int y) {
	int ret = 0;
	int l = 0;
	Point pivot(x, y);
	vector<tuple<Point, int, int>> events;

	for (auto &[x0, x1, y2] : deposits) {
		if (y2 == y){
			if (x0 == x || x1 == x) l = abs(x0 - x1);
			continue;
		}
		Point p1(x0, y2), p2(x1, y2);
		p1 = (y2 < y) ? pivot - p1 : p1 - pivot;
		p2 = (y2 < y) ? pivot - p2 : p2 - pivot;
		
		int length = abs(x1 - x0);

		if (p1.first < p2.first) swap(p1, p2);
		events.emplace_back(p1, 0, length);//in
		events.emplace_back(p2, 1, length);//out
	}

	sort(all(events), [](auto &e1,  auto &e2) {
			auto &[p1, v1, l1] = e1;
			auto &[p2, v2, l2] = e2;

			ll ccw = p1 * p2;
			if (ccw) return ccw > 0;
			return v1 < v2;
			});

	int acc_sum = 0;
	for (auto &[p, v, l] : events) {
		if (!v) acc_sum += l;
		else acc_sum -= l;
		ret = max(ret, acc_sum);
	}

	return ret + l;
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x0, x1, y;
		scanf("%d%d%d", &x0, &x1, &y);
		deposits.emplace_back(x0, x1, y);
	}

	int ans = 0;

	for (auto &[x0, x1, y] : deposits) ans = max({ans, solve(x0, y), solve(x1, y)});

	printf("%d", ans);
}