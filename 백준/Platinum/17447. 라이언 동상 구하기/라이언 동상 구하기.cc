#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

typedef pair<int, int> Point;
typedef long long ll;
const ll INF = 500 * 500 * 1e5;
int N, M;
vector<tuple<Point, int>> statues;
vector<vector<ll>> left_top, right_top, left_bottom, right_bottom; 

int ccw(Point a, Point b, Point c) {
	int ret = (b.first - a.first) * (c.second - b.second) - 1LL * (b.second - a.second) * (c.first - b.first);
	return ret > 0 ? 1 : ret? -1 : 0;
}

void add(bool left, bool top, vector<vector<ll>> &v) {
	int xx = left ? 0 : N;
	int yy = top ? N : 0;
	v.resize(N);

	for (int i = 1; i < N; i++) {
		Point p(xx, i);
		v[i].resize(N);

		for (int j = 1; j < N; j++) {
			Point q(j, yy);

			for (auto &statue: statues) {
				Point &s = get<0>(statue);
				if (left == top) {
					if (ccw(p, q, s) > 0) {
						v[i][j] += get<1>(statue);
					}
				}
				else if (ccw(p, q, s) < 0) {
					v[i][j] += get<1>(statue);
				}
			}
		}
	}
}

int main() {
	scanf("%d%d", &N, &M);

	long long sum = 0;
	for (int i = 0; i < M; i++) {
		int x, y, v;
		scanf("%d%d%d", &x, &y, &v);
		statues.emplace_back(Point(x, y), v);
		sum += v;
	}

	add(1, 1, left_top);
	add(1, 0, left_bottom);
	add(0, 1, right_top);
	add(0, 0, right_bottom);
	
	ll min_partial_sum = INF;

	for (int left = 1; left < N; left++) {
		for (int right = 1; right < N; right++) {
			ll min_top = INF;
			ll min_bottom = INF;

			for (int top = 1; top < N; top++) {
				min_top = min(min_top, left_top[left][top] + right_top[right][top]);
			}

			for (int bottom = 1; bottom < N; bottom++) {
				min_bottom = min(min_bottom, left_bottom[left][bottom] + right_bottom[right][bottom]);
			}

			min_partial_sum = min(min_partial_sum, min_top + min_bottom);
		}
	}

	printf("%lld", sum - min_partial_sum);
}