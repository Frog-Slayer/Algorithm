#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const double EPS = 1e-9;
typedef pair<double, double> Point2;

struct Point{ 
	double x;
	double y;
	double z;

	Point(): x(0), y(0), z(0) {}

	Point(double x, double y, double z): x(x), y(y), z(z) {}

	Point intersect_z_plane_from(const Point &o) { 
		double dz = z - o.z;
		double t = -o.z / dz;

		Point out = (*this - o) * t;
		out = out + o;
		out.z = 0;

		return out;
	}

	Point operator+(const Point &o) { 
		return Point(x + o.x, y + o.y, z + o.z);
	}

	Point operator-(const Point &o) { 
		return Point(x - o.x, y - o.y, z - o.z);
	}

	Point operator*(const double d) { 
		return Point(d * x, d * y, d* z);
	}
};

vector<Point2> convex_hull(vector<Point2> &vertex) { 
	auto ccw = [](const Point2& a, const Point2& b, const Point2& c) -> double {
		return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
	};

	auto dist = [&](const Point2& p) -> double { 
		return (p.first - vertex[0].first) * (p.first - vertex[0].first) + (p.second - vertex[0].second) * (p.second - vertex[0].second);
	};

	sort(all(vertex),
		[](const Point2 &a, const Point2& b) -> bool {
			if (fabs(a.second - b.second) < EPS) return a.first < b.first;
			return a.second < b.second;
	});

	sort(vertex.begin() + 1, vertex.end(),
		[&](const Point2& a, const Point2& b) -> bool { 
			double d = ccw(vertex[0], a, b);
			if (fabs(d) <= EPS) return dist(a) < dist(b);
			return d > 0;
	});
	
	stack<int> stk;

	stk.push(0);
	stk.push(1);

	int N = vertex.size();
	int next = 2;

	while (next < N) {
		while (stk.size() >= 2) {
			int second = stk.top();
			stk.pop();
			int first = stk.top();
			if (ccw(vertex[first], vertex[second], vertex[next]) > EPS) {
				stk.push(second);
				break;
			}
		}
		stk.push(next++);
	}

	vector<Point2> ret;

	while (!stk.empty()) { 
		Point2 p = vertex[stk.top()];
		stk.pop();

		ret.emplace_back(p);
	}

	return ret;
}

double area(const vector<Point2>& hull) {
	double ret = 0;
	int n = hull.size();

	for (int i = 0; i < n; i++) { 
		int j = (i + 1) % n;
		ret += hull[i].first * hull[j].second - hull[i].second * hull[j].first;
	}

	return fabs(ret) / 2;
}

int main() { 
	fastio;

	Point p1, p2, light;

	cin >> p1.x >> p1.y >> p1.z >> p2.x >> p2.y >> p2.z;
	cin >> light.x >> light.y >> light.z;

	if (light.z <= p1.z || light.z <= p2.z) { 
		cout << -1;
		return 0;
	} else { 
		vector<Point2> points;

		for (int i = 0; i < 2; i++) { 
			double x, y, z;
			x = i? p1.x : p2.x;
			for (int j = 0; j < 2; j++) { 
				y = j ? p1.y : p2.y;
				for (int k = 0; k < 2; k++) { 
					z = k ? p1.z : p2.z;
					Point p(x, y, z);
					Point z0 = p.intersect_z_plane_from(light);
					points.emplace_back(z0.x, z0.y);
				}
			}
		}

		sort(all(points));
		points.erase(unique(all(points)), points.end());

		vector<Point2> hull = convex_hull(points);

		if (hull.size() < 3) { 
			cout << 0;
			return 0;
		}

		cout << fixed << setprecision(10) << area(hull);
	}
}