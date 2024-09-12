#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
#define all(v) v.begin(), v.end()

typedef long long ll;
typedef pair<ll ,ll> Point;
typedef pair<Point, Point> Segment;
int N;

Point operator+(Point &p1, Point &p2) { return Point(p1.first + p2.first, p1.second + p2.second); }
Point operator-(const Point &p1, const Point &p2) { return Point(p1.first - p2.first, p1.second - p2.second); }
ll operator*(const Point &p1, const Point &p2) { return p1.first * p2.second - p1.second * p2.first; }

vector<Segment> meteors;
vector<tuple<Point, int, int>> events;

struct Compare{
	bool operator()(const int& i1, const int &i2) const {
		Segment &seg1 = meteors[i1], &seg2 = meteors[i2];
		if (seg1.first * seg2.first < 0) return (seg2.first - seg2.second) * (seg1.first - seg2.second) < 0;
		return (seg1.first - seg1.second) * (seg2.first - seg1.second) > 0;
	}
};

set<int, Compare> seg_set;
set<int> ans;

int main() {
	int N;
	scanf("%d", &N);
	
	for (int i = 0; i < N; i++){
		int m;
		scanf("%d", &m);

		vector<Point> tmp;
		for (int j = 0; j < m; j++) {
			int x, y;
			scanf("%d%d", &x, &y);
			tmp.emplace_back(x, y);
		}

		sort(all(tmp), [&](Point &p1, Point &p2) { return p1 * p2 > 0; });
		meteors.emplace_back(tmp.front(), tmp.back());
	}

	for (int i = 0; i < meteors.size(); i++) {
		auto &[p1, p2] = meteors[i];
		events.emplace_back(p1, 0, i);
		events.emplace_back(p2, 1, i);
	}

	sort(all(events), [](auto &e1, auto &e2) {
			auto &[p1, v1, i1] = e1;
			auto &[p2, v2, i2] = e2;
			return p1 * p2 > 0;
			});

	for (int i = 0, j = 0; i < events.size(); i = j) {
		while (j < events.size() && get<0>(events[i]) * get<0>(events[j]) == 0) j++;

		for (int k = i; k < j; k++) {
			auto &[p, v, s] = events[k];
			if (!v) seg_set.insert(s);
			else seg_set.erase(s);

			if (!seg_set.empty()) ans.insert(*seg_set.begin());
		}
	}

	printf("%ld", N - ans.size());
}
