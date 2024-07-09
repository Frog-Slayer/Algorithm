#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define x first
#define y second

typedef long long ll;
typedef pair<int, int> Vector2;
const int MAX_N = 2000;
int N;

Vector2 operator-(Vector2 v1, Vector2 v2) { return {v1.x - v2.x, v1.y - v2.y};}
ll operator*(Vector2 v1, Vector2 v2) { return (ll)v1.x * v2.y - (ll) v2.x * v1.y; }
ll operator!(Vector2 v) { return (ll)v.x * v.x + (ll)v.y * v.y; }

vector<Vector2> v, origin;

struct Line {
	int i, j;
	bool is_vertical = false; //두 점을 이은 선분에 수직인 직선에 사영하는가?
	Vector2 vec;

	Line(int _i, int _j, bool _is_vertical) {
		i = _i; 
		j = _j; 
		Vector2 &p1 = v[i];
		Vector2 &p2 = v[j];
		is_vertical = _is_vertical;

		vec = p2 - p1;
		if (!is_vertical) vec = (vec.y < 0) ? Vector2( -vec.y, vec.x ) : Vector2( vec.y, -vec.x ); 
	}

	bool operator<(const Line &rhs) {
		long long cross = vec * rhs.vec; 
		if (cross) return cross > 0;
		return tie(is_vertical, i, j) < tie(rhs.is_vertical, i, j);
	}
};

vector<Line> lines;
int p[2000];

double dot_line_dist(Vector2 &p1, Vector2 &p2, Vector2 &q) {
	double cross = fabs((p1 - p2) * (q - p2)); 
	double dist = sqrt(!(p1 - p2));

	return cross / dist;
}


void solve(){ 
	sort(v.begin(), v.end());
	origin.insert(origin.end(), v.begin(), v.end());

	for (int i = 0; i < N; i++) {
		p[i] = i;
		for (int j = i + 1; j < N; j++) {
			lines.emplace_back(i, j, false);
			lines.emplace_back(i, j, true);
		}
	}

	sort(lines.begin(), lines.end());

	double ans = 0;

	for (int i = 0; i < lines.size(); i++) {
		int a = lines[i].i, b = lines[i].j;
		Vector2 &p1 = origin[a], &p2 = origin[b];

		if (lines[i].is_vertical) {
			swap(p[a], p[b]);
			a = p[a], b = p[b];
			swap(v[a], v[b]);

			if (a > b) swap(a, b);

			if (a) ans = max(ans, dot_line_dist(p1, p2, v[a - 1]));
			if (b < N - 1) ans = max(ans, dot_line_dist(p1, p2, v[b + 1]));
		}
		else if (abs(p[a] - p[b]) == 1) ans = max(ans, sqrt(!(v[p[a]] - v[p[b]])));

	}

	printf("%.10f", ans / 2);
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		v.emplace_back(x, y);
	}

	solve();
}
