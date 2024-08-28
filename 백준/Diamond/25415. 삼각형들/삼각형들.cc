#include <iostream>
#include <algorithm>
#include <tuple>
using namespace std;

typedef long long ll;

int N;
ll A, B;
pair<int, int> cur_a, cur_b;

struct Point {
	ll x;
	ll y;

	Point(pair<int, int> p) : x(p.first), y(p.second) {}
	Point(ll _x, ll _y) : x(_x), y(_y) {}

	Point operator+(const Point& p) { return {x + p.x, y + p.y}; }
	Point operator-(const Point& p) {
		return {x - p.x, y - p.y};
	}

	ll operator*(const Point& p) {
		return llabs(x * p.y - y * p.x);
	}

	bool operator<(const ll val) const {
		Point a(cur_a), b(cur_b);
		return (a - b)*(a - *this) < val;
	}

	bool operator>(const ll val) const {
		Point a(cur_a), b(cur_b);
		return (a - b)*(a - *this) > val;
	}
};

bool operator<(const ll &val, const Point &p) {
	Point a(cur_a), b(cur_b);
	return val < (a - b)*(a - p);
}

bool operator>(const ll &val, const Point &p) {
	Point a(cur_a), b(cur_b);
	return val > (a - b)*(a - p);
}

vector<Point> points;

struct Line {
	int i, j;
	long long dx, dy;

	Line(int _i, int _j, Point pi, Point pj) {
		i = _i;
		j = _j;
		dx = pi.x - pj.x; 
		dy = pi.y - pj.y; 
	}
	
	bool operator==(const Line &rhs) {
		return dx * rhs.dy == dy * rhs.dx;
	}

	bool operator<(const Line &rhs) {
		long long slp = dy * rhs.dx, r_slp = rhs.dy * dx;
		return tie(slp, i, j) < tie(r_slp, rhs.i, rhs.j);
	}
};

vector<Line> lines;

ll solve(){
	sort(points.begin(), points.end(), [](Point &p1, Point &p2) {
			if (p1.x != p2.x) return p1.x < p2.x;
			return p1.y < p2.y;
			});

	vector<int> p;
	ll ret = 0;

	for (int i = 0; i < N; i++) p.push_back(i);

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			lines.emplace_back(i, j, points[i], points[j]);
		}
	}

	sort(lines.begin(), lines.end());
 
	for (int i = 0, j = 0; i < lines.size(); i = j) {
		while (j < lines.size() && lines[i] == lines[j]) j++;
		for (int k = i; k < j; k++) {
			int a = lines[k].i, b = lines[k].j;
			swap(points[p[a]], points[p[b]]);
			swap(p[a], p[b]);

			a = p[a], b = p[b];

			if (a > b) swap(a, b);
			//넓이가 B/2가 되는 가장 먼 점, A/2가 되는 가장 가까운 점 찾기
			cur_a = { points[a].x, points[a].y };
			cur_b = { points[b].x, points[b].y };
			
			int right_greater_A = lower_bound(points.begin() + b, points.end(), A) - points.begin();
			int right_greater_B = upper_bound(points.begin() + b, points.end(), B) - points.begin();

			ret += (right_greater_B - right_greater_A);

			int left_greater_A = upper_bound(points.begin(), points.begin() + a, A, greater<>()) - points.begin();
			int left_greater_B = lower_bound(points.begin(), points.begin() + a, B, greater<>()) - points.begin();

			ret += (left_greater_A - left_greater_B);
		}
	}
	
	return ret;
}

int main() {
	scanf("%d%lld%lld", &N, &A, &B);

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		points.emplace_back(x, y);
	}

	ll ans = solve();
	printf("%lld", ans / 3);

}