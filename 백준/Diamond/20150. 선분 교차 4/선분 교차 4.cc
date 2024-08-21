#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;
#define all(v) v.begin(), v.end()

typedef __int128 ll;
typedef pair<ll, ll> Point;
typedef long double ld;
const ll K = 2e9 + 7;//나오지 않을 기울기
ll cur;

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

		ld scope1 = 1.0 * (y2 - y1) / (x2- x1);
		ld scope2 = 1.0 * (y4 - y3) / (x4- x3);

		ld eval1 = scope1 * (cur - x1) + y1;
		ld eval2 = scope2 * (cur - x3) + y3;

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
	ll ret = (b.first - a.first) * (c.second - b.second) - (b.second - a.second) * (c.first - b.first);

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
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		segments.emplace_back(Point(x1, y1), Point(x2, y2), i);
	}


	printf("%d", solve());

}