#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)); v.erase(unique(all(v)), v.end())

typedef long long ll;
int N;
vector<int> S;
vector<pair<int, int>> v;

struct Event {
	int x;
	int y1;
	int y2;
	int val;

	Event(int _x, int _y1, int _y2, int _val) : x(_x), y1(_y1), y2(_y2), val(_val) {}

	bool operator<(const Event& e) {
		if (x != e.x) return x < e.x;
		return val < e.val;
	}
};

struct Segtree {
	vector<int> tree, lazy;
	int N;

	Segtree(int sz) {
		N = sz;
		tree.resize(sz * 4 + 4);
		lazy.resize(sz * 4 + 4);
	}

	void propagate(int node, int start, int end) {
		tree[node] += lazy[node];

		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}

		lazy[node] = 0;
	}

	void update(int node, int start, int end, int left, int right, int val) {
		propagate(node, start, end);
		if (right < start || end < left) return;
		if (left <= start && end <= right) {
			lazy[node] += val;
			propagate(node, start, end);
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, val);
		update(node * 2 + 1, mid + 1, end, left, right, val);
		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}

	void update(int left, int right, int val) {
		update(1, 0, N, left, right, val);
	}

	int query() {
		propagate(1, 0, N);
		return tree[1];
	}
};

bool solve(int cur) {
	vector<Event> events;
	vector<int> yy;

	for (int i = 0; i < N; i++) {
		int volume = S[i] * cur;
		int x = v[i].first, y = v[i].second;
		events.emplace_back(x - volume, y - volume, y + volume, 1);
		events.emplace_back(x + volume, y - volume, y + volume, -1);
		yy.emplace_back(y - volume);
		yy.emplace_back(y + volume);
		yy.emplace_back(y + volume - 1);
	}

	sort(all(events));
	compress(yy);

	Segtree tree(yy.size());

	for (int j = 0, i = 0; i < 2 * N; i = j) {
		while (events[j].x == events[i].x) {
			int y1 = events[j].y1, y2 = events[j].y2;

			y2--;
			y1 = lower_bound(all(yy), y1) - yy.begin();
			y2 = lower_bound(all(yy), y2) - yy.begin();

			tree.update(y1, y2, events[j].val);
			j++;
		}

		if (tree.query() > 1) return false;
	}

	return true;
}

int main(){ 
	scanf("%d", &N);

	for (int i = 0; i < N; i++){
		int s;
		scanf("%d", &s);
		S.emplace_back(s);
	}

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		v.emplace_back(x + y, x - y);
	}

	int left = 1, right = 1000000;
	while (left < right) {
		int mid = (left + right) / 2;

		if (solve(mid)) left = mid + 1;
		else right = mid;
	}

	printf("%d", right - 1);
}