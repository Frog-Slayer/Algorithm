#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()
#define fastio cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false)

typedef long long ll;

struct Point {
	int idx;
	int x;
	int y;
	int prev;
	int next;

	Point(int _idx, int _x, int _y) : idx(_idx), x(_x), y(_y) {}
	Point(int _x, int _y) : x(_x), y(_y) {}

	Point operator-(const Point &p) {
		return Point(x - p.x, y - p.y);
	}

	ll operator*(const Point& p) {
		return 1LL * x * p.y - 1LL * y * p.x;
	}
};

int main() {
	fastio;
	int N;
	cin >> N;

	vector<Point> points;

	for (int i = 0; i < N; i++) {
		int x, y;
		cin >> x >> y;
		points.emplace_back(i, x, y);
	}

	vector<Point> px(points);
	vector<Point> py(points);

	sort(all(px), [](auto &p1, auto &p2) {
			if (p1.x != p2.x) return p1.x < p2.x;
			return p1.y < p2.y;
			});

	sort(all(py), [](auto &p1, auto &p2) {
			if (p1.y != p2.y) return p1.y < p2.y;
			return p1.x < p2.x;
			});

	string s;
	cin >> s;

	vector<bool> visited(N);
	vector<int> order(N);

	int left = 0, right = N - 1;
	int up = N - 1, down = 0;

	for (int i = 0; i < N - 2; i++) {
		switch (s[i]) {
			case 'L': while (left <= right && visited[px[left].idx]) left++; order[i] = px[left].idx; break;
			case 'R': while (left <= right && visited[px[right].idx]) right--; order[i] = px[right].idx; break; 
			case 'U': while (down <= up && visited[py[up].idx]) up--; order[i] = py[up].idx; break;
			case 'D': while (down <= up && visited[py[down].idx]) down++; order[i] = py[down].idx;
		}

		visited[order[i]] = true;
	}

	left = px.back().idx, right = px.front().idx;
	down = py.back().idx, up = py.front().idx;

	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			if (points[left].x > points[i].x) left = i;
			if (points[right].x < points[i].x) right = i;
			if (points[down].y  > points[i].y) down = i;
			if (points[up].y  < points[i].y) up = i;
		}
	}

	//2개
	//printf("left: %d, right: %d, up: %d, down: %d\n", left, right, up, down);
	points[left].next = points[left].prev = right;
	points[right].next = points[right].prev = left;

	vector<ll> area(N);

	for (int i = N - 3; i >= 0; i--) {
		area[i] = area[i + 1];

		int closest;
		switch (s[i]) {
			case 'L': closest = left; break;
			case 'R': closest = right; break;
			case 'U': closest = up; break;
			case 'D': closest = down; break;
		}

		Point& current = points[order[i]];

		current.prev = current.next = closest;

		ll tmp;
		while ((tmp = (points[current.prev] - current) * (points[points[current.prev].prev] - points[current.prev])) > 0) {
			area[i] += tmp;
			current.prev = points[current.prev].prev;
		}
	
		while ((tmp = (points[current.next] - current) * (points[points[current.next].next] - points[current.next])) < 0) {
			area[i] -= tmp;
			current.next = points[current.next].next;
		}

		points[current.prev].next = current.idx;
		points[current.next].prev = current.idx;

		if (points[left].x > current.x) left = current.idx;
		if (points[right].x < current.x) right = current.idx;
		if (points[down].y  > current.y) down = current.idx;
		if (points[up].y  < current.y) up = current.idx;
	}

	cout << fixed;
	cout.precision(1);
	for (int i = 0; i < N - 2; i++) cout << area[i] / 2 << '.' << (area[i] % 2 ? 5 : 0)  << '\n';

}