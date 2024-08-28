#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()

struct Point {
	int x, y;

	Point(int _x, int _y) : x(_x), y(_y) {}

	bool operator<(const Point &p) const {
		if (y != p.y) return y < p.y;
		return x < p.x;
	}

	bool operator==(const Point &p) {
		return x == p.x && y == p.y;
	}

	Point operator+(const Point &p) {
		return {x + p.x, y + p.y};
	}

	Point operator-(const Point &p) {
		return {x - p.x, y - p.y};
	}

	int operator*(const Point &p) {
		return x * p.y - y * p.x;
	}
};

vector<Point> red, green, blue;
char buffer[51];

int dist(Point a, Point b){
	int x = a.x - b.x, y = a.y - b.y; 
	return x * x + y * y;
}

int ccw(Point &a, Point &b,  Point &c) {
	int ccw = (b - a) * (c - a);
	if (ccw < 0) return -1;
	if (ccw) return 1;
	return 0;
}

vector<Point> convex_hull(vector<Point> &p) {
	if (p.size() < 2) return p;
	vector<Point> res;
	sort(all(p));

	sort(p.begin() + 1, p.end(), [&](Point &a, Point &b){
		int c = ccw(p[0], a, b);
		if (c) return c > 0;
		return dist(p[0], a) < dist(p[0], b);
	});

	res.push_back(p[0]);
	res.push_back(p[1]);

	int next = 0;
	while (next < p.size()) {
		while (res.size() >= 2) {
			Point second = res.back();
			res.pop_back();
			Point first = res.back();
			if (ccw(first, second, p[next]) >= 0) {
				res.push_back(second);
				break;
			}
		}
		res.push_back(p[next++]);
	}

	reverse(p.begin() + 1, p.end());
	for (int i = 1; i < p.size() - 1; i++) {
		if (ccw(p[0], p[i], p[i + 1]) == 0) {
			res.push_back(p[i]); 
			res.push_back(p[i + 1]); 
		}
		else break;
	}

	sort(all(res));
	res.erase(unique(all(res)), res.end());

	return res;
}

vector<Point> max_triangles(Point &a, Point &b, vector<Point> &points) {
	vector<Point> res;
	int max_area = 0;
	for (auto &p: points) {
		int area = abs((a - b)*(a - p));
		if (area > max_area) {
			res.clear();
			max_area = area;
		}

		if (max_area == area) res.push_back(p);
	}
	return res;
}

int main() {
	int N, M;
	scanf("%d%d", &N, &M);

	for (int i = 0; i < N; i++) {
		scanf("%s", buffer);
		for (int j = 0; j < M; j++) {
			switch (buffer[j]) {
				case 'R': red.emplace_back(i, j); break;
				case 'G': green.emplace_back(i, j); break;
				case 'B': blue.emplace_back(i, j); break;
			}
		}
	}

	int ans = red.size() * green.size() * blue.size();
	if (ans) {
		red = convex_hull(red);
		green = convex_hull(green);
		blue = convex_hull(blue);

		for (auto &r : red) {
			for (auto &g : green) {
				auto filtered = max_triangles(r, g, blue);

				int area = abs((r - g) * (r - filtered[0]));
				for (auto &b : filtered) {
					Point p = max_triangles(r, b, green)[0];
					if (abs((r - b) * (r - p)) != area) continue;
					p = max_triangles(g, b, red)[0];
					if (abs((b - g) * (b - p)) != area) continue;
					ans--;
				}
			}
		}
	}
	
	printf("%d", ans);
}