#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
#define all(v) v.begin(), v.end()
typedef long long ll;
typedef pair<int, int> Point;

vector<Point> v;
ll operator!(const Point &p) { return (ll)p.first * p.first + (ll)p.second * p.second; }
ll operator*(Point &p1, Point &p2) { return (ll)p1.first * p2.first + (ll)p1.second * p2.second; }
ll operator/(Point &p1, Point &p2) { return (ll)p1.first * p2.second - (ll)p1.second * p2.first; }

struct Fenwick {
	int N;
	vector<int> tree;

	void resize(int _N) {
		N = _N;
		tree.resize(N + 1);
	}

	void clear() {
		tree.clear();
		tree.resize(N + 1);
	}

	void update(int i, int val) {
		while (i <= N) {
			tree[i]++;
			i += (i & -i);
		}
	}

	int query(int i) {
		int ret = 0;
		while (i > 0) {
			ret += tree[i];
			i -= (i & -i);
		}
	
		return ret;
	}

	int query(int left, int right) {
		return query(right) - query(left - 1);
	}

} tree;

ll ans;

void solve(int idx) {
	vector<Point> B;
	Point &a = v[idx];

	for (Point &p : v) {
		if (p.first <= a.first && p.second >= a.second) continue;
		B.emplace_back(p.first - a.first, p.second - a.second);
	}

	sort(all(B), [&](Point &p1, Point &p2) {
			Point o(0, 0);
			if ((p1 < o)^(p2 < o)) return p1 < p2; 
			return p1/p2 > 0; 
			});

	int b = 0;
	while (b < B.size() && B[b].first <= 0) b++;

	int c = 0, d = b;

	vector<pair<int, int>> range(B.size());

	while (b < B.size() && B[b].second < 0) {
		while (c < b && B[c] * B[b] <= 0) c++;
		while (d < B.size() && B[d] * B[b] > 0) d++;
		range[b++] = { c + 1, d }; 
	}

	vector<pair<ll, int>> dist(B.size());

	for (int i = 0; i < B.size(); i++) dist[i] = { !B[i], i };

	sort(all(dist));
	tree.clear();

	for (int i = 0, j = 0; i < B.size(); i = j) {
		while (j < B.size() && dist[i].first == dist[j].first) j++;

		for (int k = i; k < j; k++) {
			int b = dist[k].second;
			if (B[b].first > 0 && B[b].second < 0) {
				int l = range[b].first, r = range[b].second; 
				ans += (ll)tree.query(l, b + 1) * (ll)tree.query(b + 2, r);
			}
		}

		for (int k = i; k < j; k++) tree.update(dist[k].second + 1, 1); 
	}
}

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		v.emplace_back(x, y);
	}

	tree.resize(N - 1);
	for (int i = 0; i < N; i++) solve(i);

	printf("%lld", ans);

}