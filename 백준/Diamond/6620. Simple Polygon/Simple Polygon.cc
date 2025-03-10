#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;
#define all(v) v.begin(), v.end()

typedef __int128  ll;
typedef pair<ll, ll> Point;
typedef long double ld;
ll cur, K;
bool is_start;

struct Segment {
	Point s, e;
	int idx;

	Segment(Point _s, Point _e, int _idx) {
		s = {_s.first + K * _s.second, -K * _s.first + _s.second };
		e = {_e.first + K * _e.second, -K * _e.first + _e.second };
		idx = _idx;

		if (s > e) swap(s, e);
	}

	bool operator<(const Segment& rhs) const {
		auto &[x1, y1] = s;
		auto &[x2, y2] = e;
		auto &[x3, y3] = rhs.s;
		auto &[x4, y4] = rhs.e;
	
		ll curx = cur;

		ll eval1 = (y2 - y1) * (x4- x3) * (curx - x1) + y1 * (x2- x1) * (x4- x3);
		ll eval2 = (y4 - y3)* (x2- x1) * (curx - x3) + y3 * (x2- x1) * (x4- x3);

		if (eval1 != eval2) return eval1 < eval2;

		curx += (is_start ? 1 : -1);

		eval1 = (y2 - y1) * (x4- x3) * (curx- x1) + y1 * (x2- x1) * (x4- x3);
		eval2 = (y4 - y3)* (x2- x1) * (curx- x3) + y3 * (x2- x1) * (x4- x3);

		return eval1 < eval2;

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
	ll ret = (b.first - a.first) * (c.second - b.second) - (b.second - a.second) * (c.first - b.first);
	return ret > 0 ? 1 : ret ? -1 : 0;
}

bool intersect(const Segment& seg1, const Segment& seg2){
	Point p1 = seg1.s, p2 = seg1.e;
	Point p3 = seg2.s, p4 = seg2.e;

	int o1 = ccw(p1, p2, p3), o2 = ccw(p1, p2, p4);
	int o3 = ccw(p3, p4, p1), o4 = ccw(p3, p4, p2);

	if (o1 * o2 == 0 && o3 * o4 == 0) {
		if (!(o1 || o2 || o3 || o4)) return !(p4 <= p1 || p2 <= p3);
		if (p1 == p3 || p1 == p4 || p2 == p3 || p2 == p4) return false;
		return !(p2 < p3 || p4 < p1);
	}

	return o1 * o2 <= 0 && o3 * o4 <= 0;
}

vector<Event> events;
vector<Segment> segments;
multiset<Segment> ms;

bool solve() {
	for (auto &[s, e, idx] : segments) {
		events.emplace_back(s.first, s.second, 1, idx);
		events.emplace_back(e.first, e.second, 0, idx);
	}

	sort(all(events));

	for (auto &[x, y, val, idx] : events) {
		cur = x;
		is_start = val;

		if (val) {
			auto it = ms.insert(segments[idx]);
			auto nxt = next(it);
			auto prv = prev(it);

			if (nxt != ms.end() && intersect(*nxt, *it)) return true; 
			if (it != ms.begin() && intersect(*prv, *it)) return true;
		}
		else {
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
	while (1) {

		events.clear();
		segments.clear();
		ms.clear();

		int N;
		scanf("%d", &N);
		if (!N) break;

		vector<tuple<int, int, int, int>> tmp;
		vector<Point> points;
		set<ll> kset;

		for (int i = 0; i < N; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			points.emplace_back(x, y);
		}

		for (int i = 0; i < N; i++) {
			auto [x1, y1] = points[i];
			auto [x2, y2] = points[(i + 1) % N];

			tmp.emplace_back(x1, y1, x2, y2);

			if (y1 != y2) kset.insert((x2 - x1) / (y2 - y1)); 
		}

		while (kset.find(K) != kset.end()) { K++; }

		for (int i = 0; i < N; i++) {
			auto &[x1, y1, x2, y2] = tmp[i];
			segments.emplace_back(Point(x1, y1), Point(x2, y2), i);
		}

		printf("%s\n", solve() ? "NO" : "YES");
	}
}