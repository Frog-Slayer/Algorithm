#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define x first
#define y second

typedef pair<int, int> Point;
typedef long long ll;
int N;
vector<Point> v;
vector<int> p;

Point operator-(Point &p1, Point &p2) { return Point(p1.x - p2.x, p1.y - p2.y); }
ll operator*(Point p1, Point p2) { return (ll)p1.x * p2.y - (ll)p1.y * p2.x ; }

struct Line {
	int i, j;
	ll dx, dy;

	Line (int _i, int _j) {
		i = _i, j = _j;
		dx = v[j].x - v[i].x;
		dy = v[j].y - v[i].y;
	}

	bool operator<(const Line &rhs) {
		ll slp =  dy * rhs.dx, rslp = dx * rhs.dy; 
		return tie(slp, i, j) < tie(rslp, rhs.i, rhs.j);
	}
};

vector<Line> lines;

void solve() {
	sort(v.begin(), v.end());

	p.resize(N);
	for (int i = 0; i < N; i++) p[i] = i;

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) lines.emplace_back(i, j);
	}

	sort(lines.begin(), lines.end());

	ll min_area = 8e18;
	ll min_cnt = 0;
	ll diag = 0;

	for (int i = 0; i < lines.size(); i++) {
		int a = lines[i].i, b = lines[i].j;

		swap(p[a], p[b]);
		a = p[a], b = p[b];
		if (a > b) swap(a, b);
		swap(v[a], v[b]);

		diag += (ll)a * (N - 1 - b);

		for (int j = max(a - 2, 0); j < a; j++) {
			for (int k = b + 1; k < min(b + 3, N); k++) {
				ll area = llabs((v[a] - v[j]) * (v[b] - v[a])) + llabs((v[a] - v[k]) * (v[b] - v[a]));

				//세 점이 한 직선 위에 있는 경우는 없음
				int cross_jka = (v[k] - v[j]) * (v[k] - v[a]) > 0 ? 1 : -1;
				int cross_jkb = (v[k] - v[j]) * (v[k] - v[b]) > 0 ? 1 : -1; 

				bool is_non_convex = cross_jka * cross_jkb > 0 ? true : false;

				if (area < min_area) {
					min_area = area;
					min_cnt = is_non_convex ? 2 : 1;
				}
				else if (area == min_area){
					min_cnt += is_non_convex ? 2 : 1;
				}
			}
		}
	}

	printf("%lld", diag + min_cnt);
}

int main(){ 
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		v.emplace_back(x, y);
	}

	solve();
}