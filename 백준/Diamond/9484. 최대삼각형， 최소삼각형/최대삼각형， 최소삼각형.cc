#include <iostream>
#include <algorithm>
using namespace std;

int N;
vector<pair<int, int>> v;
vector<int> p(2000);
vector<pair<int, int>> slopes;

int triangle(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
	return abs((b.first - a.first) * (c.second - b.second) - (b.second - a.second) * (c.first - b.first));
}

void solve(){
	sort(v.begin(), v.end());

	for (int i = 0; i < N; i++) p[i] = i;

	slopes.clear();

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			slopes.emplace_back(i, j);
		}
	}

	sort(slopes.begin(), slopes.end(), [&](pair<int, int> i, pair<int, int> j) {
			pair<int, int> p1_i = v[i.first], p2_i = v[i.second];
			pair<int, int> p1_j = v[j.first], p2_j = v[j.second];

			int dy_i = p1_i.second - p2_i.second, dx_i = p1_i.first - p2_i.first;
			int dy_j = p1_j.second - p2_j.second, dx_j = p1_j.first - p2_j.first;

			return dy_i * dx_j == dx_i * dy_j ? i < j : dy_i * dx_j < dx_i * dy_j;
			});
	
	int min_triangle = 20000 * 20000, max_triangle = 0;

	for (int i = 0, j = 0; i < slopes.size(); i = j) {
		while (j < slopes.size()) {
			pair<int, int> si= slopes[i], sj = slopes[j];
			pair<int, int> p1_i = v[si.first], p2_i = v[si.second];
			pair<int, int> p1_j = v[sj.first], p2_j = v[sj.second];

			int dy_i = p1_i.second - p2_i.second, dx_i = p1_i.first - p2_i.first;
			int dy_j = p1_j.second - p2_j.second, dx_j = p1_j.first - p2_j.first;

			if (dy_i * dx_j == dx_i * dy_j) j++;
			else break;
		}

		for (int k = i; k < j; k++) {
			int a = slopes[k].first, b = slopes[k].second;
			swap(p[a], p[b]);
			swap(v[p[a]], v[p[b]]);

			a = p[a], b = p[b];
			if (a > b) swap(a, b);

			if (a) {
				int m, M;
				min_triangle = min(min_triangle, m = triangle(v[a], v[b], v[a - 1]));
				max_triangle = max(max_triangle, M = triangle(v[a], v[b], v[0]));
			}
			if (b < N - 1) {
				int m, M;
				min_triangle = min(min_triangle, m =triangle(v[a], v[b], v[b + 1]));
				max_triangle = max(max_triangle, M = triangle(v[a], v[b], v[N - 1]));
			}
		}
	}

	printf("%.1f %.1f\n", (double)min_triangle/2, (double)max_triangle/2);

}

int main() {
	while (true) {
		scanf("%d", &N);
		if (!N) break;
		v.resize(N);

		for (int i = 0; i < N; i++) {
			scanf("%d%d", &v[i].first, &v[i].second);
		}

		solve();
	}

}