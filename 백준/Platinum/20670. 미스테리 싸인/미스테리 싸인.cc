#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef tuple<int, int> Point;
typedef long long ll;

Point operator-(const Point &p1, const Point &p2) {
	auto &[x1, y1] = p1;
	auto &[x2, y2] = p2;
	return {x1 - x2, y1 - y2};
}

ll operator*(const Point &p1, const Point &p2) {
	auto [x1, y1] = p1;
	auto [x2, y2] = p2;

	return (ll)x1 * y2 - (ll)x2 * y1;
}

int ccw(const Point &p1, const Point &p2, const Point &p3) {
	ll ret = (p2 - p1) * (p3 - p1);
	if (!ret) return 0;
	return ret < 0 ? -1 : 1;
}

bool is_in_convex(vector<Point> &polygon, Point &p) {
	
	Point &o = polygon[0];
	int left = 1, right = polygon.size() - 1;
	int olp = ccw(o, polygon[left], p), orp = ccw(o, polygon[right], p);

	if (olp <= 0 || orp >= 0) return false;

	while (left + 1 < right) {
		int mid = (left + right) / 2;
		if (ccw(o, polygon[mid], p) > 0) left = mid;
		else right = mid;
	}

	Point &b = polygon[left], &c = polygon[right];

	return ccw(b, c, p) > 0;
}

int main() {
	fastio;

	int N, M, K;
	cin >> N >> M >> K;

	vector<Point> A(N), B(M);

	for (int i = 0; i < N; i++) {
		int x, y;
		cin >> x >> y;
		A[i] = {x, y};
	}

	for (int i = 0; i < M; i++) {
		int x, y;
		cin >> x >> y;
		B[i] = {x, y};
	}

	int cnt = 0;

	for (int i = 0; i < K; i++) {
		int x, y;
		cin >> x >> y;

		Point p(x, y);

		if (!is_in_convex(A, p) || is_in_convex(B, p)) cnt++;
	}

	if (cnt) cout << cnt;
	else cout << "YES";


}
