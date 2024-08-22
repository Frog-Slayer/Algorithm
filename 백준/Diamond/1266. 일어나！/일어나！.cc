#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
#include <queue>
#include <cmath>
using namespace std;

typedef double ld;
const int START = 0;
const int INTERSECT = 1;
const int END = 2;
const int INF = 2e6 + 7;

typedef pair<ld, ld> Point;

Point operator*(const Point &p, const ld &d) { return { p.first * d, p.second * d}; }
Point operator-(const Point &p, const Point &d) { return { p.first - d.first, p.second - d.second };}
Point operator+(const Point &p, const Point &d) { return { p.first + d.first, p.second + d.second };}
ld operator*(const Point &p, const Point &d) { return p.first * d.second - p.second * d.first; }

ld cur;
struct Segment{ 
	Point s;
	Point e;
	int idx;
	ld scope;
	
	Segment(Point _s, Point _e, int _idx) {
		s = _s; e = _e;
		idx = _idx;

		if (e < s) swap(s, e);

		if (e.first == s.first) scope = INF;
		else scope = (e.second - s.second) / (e.first - s.first); 
	}

	ld eval() const {
		return scope * (cur - s.first) + s.second;
	}

	bool operator<(const Segment& rhs) const {
		ld ev1 = eval();
		ld ev2 = rhs.eval();
		
		if (ev1 != ev2) return ev1 < ev2;
		return scope < rhs.scope;
	}

	Point operator*(const Segment& rhs) const {
		ld det = (e- s) * (rhs.e - rhs.s);
		auto ret = s + (e - s) * ((rhs.s - s) * (rhs.e - rhs.s)/det);
		return ret;
	}
};

struct Event {
	ld x;
	ld y;
	int val;
	int idx1;
	int idx2;

	Event(Point p, int _val, int _idx) : x(p.first), y(p.second), val(_val), idx1(_idx), idx2(_idx) {}
	Event(Point p, int _val, int _idx1, int _idx2) : x(p.first), y(p.second), val(_val), idx1(_idx1), idx2(_idx2) {}

	bool operator<(const Event& e) const {
		return tie(x, y, val) < tie(e.x, e.y, e.val);
	}
};

int ccw(Point& a, Point& b, Point& c) {
	ld ret =  (b.first - a.first) * (c.second - b.second) - (b.second - a.second) * (c.first - b.first);
	return ret == 0 ? 0 : ret > 0 ? 1 : -1; 
}

bool intersect(const Segment& seg1, const Segment& seg2) {
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

vector<Segment> segments;
multiset<Event> events;
multiset<Segment> ms;
set<pair<int, int>> ans;

void push(Point &intersection, int idx1, int idx2) {
	if (idx1 < idx2) swap(idx1, idx2);
	Event e = Event(intersection, 1, idx1, idx2);
	if (isnan(intersection.first) || isnan(intersection.second)) ans.insert({idx1, idx2}); 
	else if (events.find(e) == events.end()) events.insert(e);
}

void solve() {
	for (auto &seg : segments) {
		auto &[s, e, idx, scope] = seg;
		events.insert(Event(s, START, idx));
		events.insert(Event(e, END, idx));
	}

	while (!events.empty()) {
		auto it = events.begin();
		auto [x, y, val, idx1, idx2] = *it;
		cur = x;

		switch (val) {
			case START :{
					auto seg = segments[idx1];
					auto it = ms.insert(seg);
					auto nxt = next(it);
					auto prv = prev(it);

					if (nxt != ms.end() && intersect(*nxt, *it)) {
						Point intersection = (*nxt) * (*it);
						push(intersection, it->idx, nxt->idx);
					}

					if (it != ms.begin() && intersect(*prv, *it)) {
						Point intersection = (*prv) * (*it);
						push(intersection, it->idx, prv->idx);
					}
					break;
				}
			case END: {
					auto seg = segments[idx1];
					auto it = ms.lower_bound(seg);

					auto nxt = next(it);
					auto prv = prev(it);

					if (it != ms.begin() && nxt != ms.end() && intersect(*prv, *nxt)) {
						Point intersection = (*prv) * (*nxt);
						push(intersection, nxt->idx, prv->idx);
					}

					ms.erase(it);

					break;
				  }
			case INTERSECT: {
					if (idx1 < idx2) swap(idx1, idx2);
					ans.insert({idx1, idx2});

					auto seg1 = segments[idx1];
					auto seg2 = segments[idx2];

					ms.erase(seg1); ms.erase(seg2);
					seg1.s = seg2.s = segments[idx1].s = segments[idx2].s = {x, y};

					if (seg2.scope < seg1.scope) swap(seg1, seg2);

					auto upper = ms.insert(seg2);
					auto upper_nxt = next(upper);

					if (upper_nxt != ms.end() && intersect(*upper, *upper_nxt)) {
						Point intersection = (*upper) * (*upper_nxt);
						push(intersection, upper->idx, upper_nxt->idx);
					}

					auto lower = ms.insert(seg1);
					auto lower_prv = prev(lower);

					if (lower != ms.begin() && intersect(*lower, *lower_prv)) {
						Point intersection = (*lower) * (*lower_prv);
						push(intersection, lower->idx, lower_prv->idx);
					}
				}
		}
		events.erase(it);
	}
}

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		segments.emplace_back(Point(x1, y1), Point(x2, y2), i);
	}

	solve();

	printf("%ld",  ans.size());
}