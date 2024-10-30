#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

typedef double ld;
typedef pair<ld, ld> Point; typedef pair<Point, Point> Segment;

const ld _45_DEGREE = atan(1);

ld operator*(Point p1, Point p2) {
	return p1.first * p2.second - p1.second * p2.first;
}

Point operator+(Point p1, Point p2) {
	return { p1.first + p2.first, p1.second + p2.second };
}

Point operator-(Point p1, Point p2) {
	return { p1.first - p2.first, p1.second - p2.second };
}

Point operator*(Point p1, ld d) {
	return { p1.first * d, p1.second * d};
}

Point operator/(Point p1, ld d) {
	return { p1.first / d, p1.second / d};
}

Point rotate(Point p, bool counter_clockwise) {
	ld a = p.first, b = p.second;
	ld angle = counter_clockwise ? _45_DEGREE : -_45_DEGREE;

	return { a * cos(angle) - b * sin(angle), a * sin(angle) + b * cos(angle)};
}

int ccw(Point &p1, Point &p2, Point &p3) {
	ld ret = (p2 - p1) * (p3 - p1);

	if (fabsl(ret) < 1e-5) return 0;
	return ret > 0 ? 1 : -1;
}

bool intersects(Segment &s1, Segment &s2) {
	Point p1 = s1.first, p2 = s1.second; 
	Point p3 = s2.first, p4 = s2.second; 

	int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
	int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

	if (!p1p2 && !p3p4) {
		if (p1 > p2) swap(p1, p2);
		if (p3 > p4) swap(p3, p4);

		return (p2 >= p3 && p4 >= p1);
	}

	return p1p2 <= 0 && p3p4 <= 0;
}

Point find_intersection(Segment s1, Segment s2) {
	Point p1 = s1.first, p2 = s1.second; 
	Point p3 = s2.first, p4 = s2.second; 

	return p1 + (p2 - p1) * ((p3 - p1) * (p4 - p3) / ((p2 - p1) * (p4 - p3)));
}

int main() {
	fastio;

	int T;
	cin >> T;

	while (T--) {
		int N;
		cin >> N;

		vector<Point> v;

		for (int i = 0; i < N; i++) {
			int x, y;
			cin >> x >> y;
			v.emplace_back(x, y);
		}

		Point cam = (v[0] + v[1]) / 2;

		Point p0 = v[0] - cam;
		Point p1 = v[1] - cam; 

		p0 = (rotate(p0, false) * 300000) + cam;
		p1 = (rotate(p1, true) * 300000) + cam;

		Segment seg1 = {cam, p0}, seg2 = {cam, p1};
		ld area = 0, total = 0;
		bool add = false;

		for (int i = 1; i < N; i++) {
			Point &p1 = v[i], &p2 = v[(i + 1) % N];
			Segment seg = {p1, p2}; 
			total += fabsl((p1 - v[0]) * (p2 - v[0]));

			bool start = intersects(seg, seg2), end = intersects(seg, seg1);

			if (start && end) {
				Point intersection1 = find_intersection(seg, seg2);
				Point intersection2 = find_intersection(seg, seg1);
				area += fabsl((intersection1 - cam) * (intersection2 - cam));
			}
			else if (start) {
				Point intersection = find_intersection(seg, seg2);
				area += fabsl((intersection - cam) * (p2 - cam));
				add = true;
			}
			else if (end) {
				Point intersection = find_intersection(seg, seg1);
				area += fabsl((intersection - cam) * (p1 - cam));
				add = false;
			}
			else if (add) {
				area += fabsl((p1 - cam) * (p2 - cam));
			}
		}

		cout <<fixed;
		cout.precision(10);
		cout << area / total << '\n';
	}
}