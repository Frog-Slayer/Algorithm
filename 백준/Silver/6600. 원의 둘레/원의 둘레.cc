#include <iostream>
#include <cmath>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const double PI = 3.141592653589793;
typedef pair<double, double> Point;

Point operator-(Point &p1, Point &p2) { 
	return { p1.first - p2.first, p1.second - p2.second };
}

double dist(Point p1, Point p2) { 
	Point d = p1 - p2;
	return sqrt(d.first * d.first + d.second * d.second);
}

int main () { 
	fastio;

	Point p1, p2, p3;

	while (cin >> p1.first >> p1.second >> p2.first >> p2.second >> p3.first >> p3.second) { 
		Point p3_1 = p3 - p1, p2_1 = p2 - p1;

		double dist_23 = dist(p2, p3);
		double angle_1 = atan2(p3_1.second, p3_1.first) - atan2(p2_1.second, p2_1.first);

		cout.precision(2);
		cout << fixed << abs(PI * dist_23 / sin(angle_1)) << '\n';
	}

}
