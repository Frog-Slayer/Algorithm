#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;
#define all(v) v.begin(), v.end()

typedef long long ll;
typedef tuple<ll, ll, int> Point;

vector<int> parent, cnt;
vector<Point> points;

int find(int a) {
	if (parent[a] == a) return a;
	return parent[a] = find(parent[a]); 
}

void uni(int a, int b) {
	a = find(a); b = find(b);
	if (a == b) return;
	parent[a] = b;
}

struct Compare{
	bool operator() (const Point& p1, const Point &p2) const {
		auto &[x1, y1, idx1] = p1;
		auto &[x2, y2, idx2] = p2;

		return y1 != y2 ? y1 < y2 : x1 < x2;
	}
};

multiset<Point, Compare> ms;

int main() {
	int M, D;
	scanf("%d%d", &M, &D);

	parent.resize(M);
	cnt.resize(M);

	for (int i = 0; i < M; i++) {
		parent[i] = i;

		int x, y;
		scanf("%d%d", &x, &y);
		points.emplace_back(x + y, x - y, i);
	}

	sort(all(points));

	for (int j = 0, i = 0; i < M; i++) {
		auto &[x, y, idx] = points[i];

		while ( j < M ) {
			auto &[x2, y2, idx2] = points[j];
			if (x2 < x - D){
				ms.erase(points[j]);
				j++;
			}
			else break;
		}

		auto it = ms.insert(points[i]);
		auto nxt = next(it);
		auto prv= prev(it);

		if (nxt != ms.end() && abs(get<1>(*nxt) - y) <= D) uni(idx, get<2>(*nxt)); 
		if (it != ms.begin() && abs(get<1>(*prv) - y) <= D) uni(idx, get<2>(*prv)); 
	}

	int ans = 0, max_sz = 0;
	for (int i = 0; i < M; i++) {
		if (find(i) == i) ans++; 
		cnt[find(i)]++;
		max_sz = max(max_sz, cnt[find(i)]);
	}

	printf("%d %d", ans, max_sz);
}
