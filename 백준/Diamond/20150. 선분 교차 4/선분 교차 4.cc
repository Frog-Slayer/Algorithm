#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef __int128 ll;
typedef pair<ll, ll> Point;

Point operator-(const Point& p1, const Point& p2) {
	return Point(p1.first - p2.first, p1.second - p2.second);
}

ll operator*(const Point& p1, const Point& p2) {
	return p1.first * p2.second - p1.second * p2.first;
}

ll K, cur;

struct Segment {
	Point s, e;
	int idx;

	Segment(Point _s, Point _e, int _idx) {
		s = Point(K * _s.first + _s.second, -1 * _s.first + K * _s.second);
		e = Point(K * _e.first + _e.second, -1 * _e.first + K * _e.second);
		idx = _idx;

		if (s > e) swap(s, e);
	}

	bool operator<(const Segment& rhs) const {
		auto &[x1, y1] = s;
		auto &[x2, y2] = e;
		auto &[x3, y3] = rhs.s;
		auto &[x4, y4] = rhs.e;

		ll eval1 = (y2 - y1) * (x4- x3) * (cur- x1) + y1 * (x2- x1) * (x4- x3);
		ll eval2 = (y4 - y3)* (x2- x1) * (cur- x3) + y3 * (x2- x1) * (x4- x3);

		if (eval1 != eval2) return eval1 < eval2;
		return idx < rhs.idx;
	}
};

struct Event {
	ll x;
	ll y;
	int val;
	int idx;

	Event(ll _x, ll _y, int _val, int _idx) : x(_x), y(_y), val(_val), idx(_idx) {} 

	bool operator<(const Event& e) {
		return tie(x, val, y, idx) < tie(e.x, e.val, e.y, e.idx);
	}
};

int ccw(Point& a, Point& b, Point& c) {
	ll ret = (b - a) * (c - b);

	return ret > 0 ? 1 : ret ? -1 : 0;
}

bool intersect(const Segment& seg1, const Segment& seg2){
	Point p1 = seg1.s, p2 = seg1.e;
	Point p3 = seg2.s, p4 = seg2.e;

	int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
	int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

	if (p1p2 == 0 && p3p4 == 0) {
		if (p1 > p2) swap(p1, p2);
		if (p3 > p4) swap(p3, p4);

		return (p2 >= p3 && p4 >= p1);
	}

	return p1p2 <= 0 && p3p4 <= 0;
}

vector<Event> events;
vector<Segment> segments;
multiset<Segment> ms;

bool solve() {
	for (auto &[s, e, idx] : segments) {
		events.emplace_back(s.first, s.second, 0, idx);
		events.emplace_back(e.first, e.second, 1, idx);
	}

	sort(all(events));

	for (auto &[x, y, val, idx] : events) {
		cur = x;
		if (!val) {//insert
			auto it = ms.insert(segments[idx]);
			auto nxt = next(it);
			auto prv = prev(it);

			if (nxt != ms.end() && intersect(*nxt, *it)) return true; 
			if (it != ms.begin() && intersect(*prv, *it)) return true;
		}
		else {//erase
			auto it = ms.lower_bound(segments[idx]);
			auto nxt = next(it);
			auto prv = prev(it);

			if (it != ms.begin() && nxt != ms.end() && intersect(*prv, *nxt)) return true; 
			ms.erase(it);
		}
	}

	return false;
}

int main() {
	fastio;

	int N;
	cin >> N;

	vector<pair<Point, Point>> points;
	set<ll> slopes;

	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		points.emplace_back(Point(x1, y1), Point(x2, y2));
		if (x1 != x2) slopes.insert((y2 - y1) / (x2 - x1));
	}

	while (slopes.find(K) != slopes.end()) K++;

	for (int i = 0; i < N; i++) {
		segments.emplace_back(points[i].first, points[i].second, i);
	}

	cout << solve();
}