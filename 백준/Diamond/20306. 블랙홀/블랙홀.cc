#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> Point;
const double PI = acos(-1);
int N, M, K;
Point singularity;
vector<Point> v, b;
vector<ld> angle;
vector<ll> ans;

Point operator*(const Point &p, const ll &d) { return { p.first * d, p.second * d}; }
Point operator-(const Point &p, const Point &d) { return { p.first - d.first, p.second - d.second };}
Point operator+(const Point &p, const Point &d) { return { p.first + d.first, p.second + d.second };}
ll operator*(const Point &p, const Point &d) { return p.first * d.second - p.second * d.first; }

ll prod(Point &a, Point &b, Point &q){
	return llabs((a - b) * (b - q)); 
}

int main() {
	scanf("%d%d%d", &N, &M, &K);
	
	int x, y;
	scanf("%lld%lld", &singularity.first, &singularity.second);

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x -= singularity.first;
		y -= singularity.second;
		v.emplace_back(x, y);
	}

	for (int i = 0; i < M; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x -= singularity.first;
		y -= singularity.second;
		b.emplace_back(x, y);
	}

	singularity = {0, 0};

	sort(all(v), [](auto &a, auto &b) {
			return atan2l(a.second, a.first) < atan2(b.second, b.first);
			});


	for (int i = 0; i < N; i++) {
		angle.emplace_back(atan2l(v[i].second, v[i].first));
	}

	for (int i = 0; i < M; i++) {
		int idx = upper_bound(all(angle), atan2l(b[i].second, b[i].first)) - angle.begin() - 1;
		idx = (idx + N) % N;
		int next = (idx + 1) % N;

		Point p = v[next] - v[idx];
		Point q = b[i] + p;
		//printf("(%lld, %lld) is between [%d](%lld, %lld), [%d](%lld, %lld). %Lf <= %Lf <=  %Lf\n", b[i].first, b[i].second, idx, v[idx].first, v[idx].second, next, v[next].first, v[next].second, angle[idx], atan2l(b[i].second, b[i].first), angle[next]);

		ll pd_b = prod(b[i], q, singularity);
		ll pd_v = prod(v[idx], v[next], singularity);

		//printf("pdb : %lld, pdv: %lld\n", pd_b, pd_v);

		if (pd_b < pd_v) ans.emplace_back(0);
		else ans.emplace_back((pd_b - 1) / pd_v);
	}

	sort(all(ans));
	printf("%lld ", ans[K - 1]);
}
