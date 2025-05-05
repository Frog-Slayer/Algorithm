#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

typedef long long ll;
typedef pair<ll, ll> Point;
const ll INF = 1e9+7;

ll operator*(const Point &p1, const Point &p2) {
	auto &[x1, y1] = p1;
	auto &[x2, y2] = p2;

	return (x1 * y2) - (x2 * y1);
}

Point operator-(const Point &p1, const Point &p2) {
	auto &[x1, y1] = p1;
	auto &[x2, y2] = p2;

	return Point(x1 - x2, y1 - y2);
}

int ccw(const Point &p1, const Point &p2, const Point &p3) {
	ll ret = (p2 - p1) * (p3 - p1);

	if (!ret) return 0;
	return ret < 0 ? -1 : 1;
}

bool intersects(Point p1, Point p2, Point p3, Point p4) {
	int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
	int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

	if (!p1p2 && !p3p4) {
		if (p1 > p2) swap(p1, p2);
		if (p3 > p4) swap(p3, p4);
		return (p2 >= p3 && p4 >= p1);
	}

	return p1p2 <= 0 && p3p4 <= 0;
}

bool is_in(const vector<Point> &v, const Point &p) {
	int cnt = 0;
	
	auto &[x, y] = p;
	Point tmp(x + 1, y + INF);

	for (int i = 0; i < v.size(); i++) {
		int j = (i + 1) % v.size();

		Point s = v[i], e = v[j];

		//선분 위에 있는지 확인.
		if (!ccw(p, s, e)) {
			auto &[xs, ys] = s;
			auto &[xe, ye] = e;

			if (min(xs, xe) <= x && x <= max(xs, xe) && min(ys, ye) <= y && y <= max(ys, ye)) return true;
			continue;
		}

		//교차 판정
		cnt += intersects(p, tmp, s, e);
	}

	return cnt % 2;
}

int main()  {
	fastio;
	
	int N;
	cin >> N;

	vector<Point> v;

	for (int i = 0; i < N; i++) {
		ll x, y;
		cin >> x >> y;

		v.emplace_back(x, y);
	}

	for (int i = 0; i < 3; i++) {
		ll x, y;
		cin >> x >> y;

		Point p(x, y);
		cout << (is_in(v, p) ? 1 : 0) << '\n';
	}
	
	
}
