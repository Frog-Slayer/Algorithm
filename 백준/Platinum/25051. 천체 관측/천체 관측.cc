#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <deque>
#include <cmath>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

struct Star{
	ll dist;
	ll s;
	double angle;
};

double diff(Star &a, Star &b) { 
	double ang = b.angle - a.angle + 2 * M_PI;
	ang = fmodl(ang, 2 * M_PI);
	return ang;
}

int main() { 
	fastio;

	int N, M;
	cin >> N >> M;

	vector<Star> stars(N);

	for (int i = 0; i < N; i++) { 
		ll x, y, z;
		cin >> x >> y >> z;

		stars[i].dist = x * x + y * y;
		stars[i].angle = atan2(y, x);
		stars[i].s = z;
	}

	vector<ll> p(M);
	ll min_p = LLONG_MAX;

	for (int i = 0; i < M; i++) { 
		cin >> p[i];
		min_p = min(min_p, p[i]);
	}

	auto sort_stars_by_angle = [&](Star &s1, Star &s2) -> bool{ 
		return s1.angle < s2.angle;
	};
	
	sort(all(stars), sort_stars_by_angle);

	stars.resize(N * 2);

	for (int i = 0; i < N; i++) stars[i + N] = stars[i];

	ll ans = -min_p;

	for (int i = 0; i < M; i++) { 
		ll sum = 0;
		for (int l = 0, r = 0; l < N; l++) { 

			while (r < 2 * N && diff(stars[l], stars[r]) <= M_PI / 2) { 
				if (stars[r].dist <= p[i]) sum += stars[r].s;
				r++;
			}

			ans = max(ans, sum - p[i]);

			if (stars[l].dist <= p[i]) sum -= stars[l].s;

		}
	}

	cout << ans;

}
