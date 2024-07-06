#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define _USE_MATH_DEFINES
using namespace std;

typedef pair<int, int> Point;
typedef double ld;

int N, R;
Point farmer;
vector<ld> angles;
vector<pair<ld, ld>> shadows;
vector<int> cnt;

int count_angle(ld angle) {
	if (binary_search(angles.begin(), angles.end(), angle)){
		int lb = lower_bound(angles.begin(), angles.end(), angle) - angles.begin();
		if (cnt[lb]) return 1;
	}

	angle -= 2 * M_PI;

	if (binary_search(angles.begin(), angles.end(), angle)){
		int lb = lower_bound(angles.begin(), angles.end(), angle) - angles.begin();
		if (cnt[lb]) return 1;
	}
	
	return 0;
}

int main(){
	scanf("%d%d", &N, &R);
	scanf("%d%d", &farmer.first, &farmer.second);

	for (int i = 0; i <= N; i++) {
		angles.push_back(atan2((i - farmer.second), (0 - farmer.first)));
		angles.push_back(atan2((i - farmer.second), (N - farmer.first)));
	}

	for (int i = 1; i < N; i++) {
		angles.push_back(atan2((0 - farmer.second), (i - farmer.first)));
		angles.push_back(atan2((N - farmer.second), (i - farmer.first)));
	}

	for (int stone = 0; stone < R; stone++){
		int p;
		scanf("%d", &p);

		vector<Point> stones;
		for (int j = 0; j < p; j++) {
			int x, y;
			scanf("%d%d", &x, &y);
			stones.emplace_back(x, y);
		}

		ld max_angle_diff = 0;
		ld mmin, mmax;

		for (int i = 0; i < p; i++) {
			ld angle_i = atan2(stones[i].second - farmer.second, stones[i].first - farmer.first);
			for (int j = i + 1; j < p; j++) {
				ld angle_j = atan2(stones[j].second - farmer.second, stones[j].first - farmer.first);
				ld max_angle = max(angle_i, angle_j), min_angle = min(angle_i, angle_j);

				ld angle_diff = max_angle - min_angle;

				if (angle_diff > M_PI) {
					angle_diff = 2 * M_PI - angle_diff; 
				}

				if (angle_diff > max_angle_diff) {
					max_angle_diff = angle_diff;
					mmin = min_angle, mmax = max_angle;
				}
			}
		}
		
		if (mmax - mmin > M_PI) {
			angles.push_back(mmax - 2 * M_PI);
			angles.push_back(mmin);

			angles.push_back(mmin + 2 * M_PI);
			angles.push_back(mmax);

			shadows.push_back({mmax - 2 * M_PI, mmin});
			shadows.push_back({mmax, mmin + 2 * M_PI});
		}
		else {
			angles.push_back(mmin);
			angles.push_back(mmax);
			shadows.push_back({mmin, mmax});
		}

	}

	sort(angles.begin(), angles.end());
	angles.erase(unique(angles.begin(), angles.end()), angles.end());
	sort(shadows.begin(), shadows.end());
	
	cnt.resize(angles.size() + 1);

	for (int i = 0; i < shadows.size(); i++) {
		int start = lower_bound(angles.begin(), angles.end(), shadows[i].first) - angles.begin();
		int end = lower_bound(angles.begin(), angles.end(), shadows[i].second) - angles.begin() + 1;

		cnt[start]++;
		cnt[end]--;
	}

	for (int i = 0; i < cnt.size(); i++) {
		if (i) cnt[i] += cnt[i - 1];
	}

	int ans = 0;

	for (int i = 0; i <= N; i++) {
		ld angle = atan2((i - farmer.second), (0 - farmer.first));
		ans += count_angle(angle);
		angle = atan2((i - farmer.second), (N - farmer.first));
		ans += count_angle(angle);
	}

	for (int i = 1; i < N; i++) {
		ld angle = atan2((0 - farmer.second), (i - farmer.first));
		ans += count_angle(angle);
		angle = atan2((N - farmer.second), (i - farmer.first));
		ans += count_angle(angle);
	}

	printf("%d\n", 4 * N - ans);
}