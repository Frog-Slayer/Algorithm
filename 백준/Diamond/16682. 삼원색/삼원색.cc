#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(x) sort(all(x)); x.erase(unique(all(x)), x.end())

typedef long long ll;
const int INF = 1e9;
int N;
vector<int> yy;
vector<tuple<int, int, int, int>> v[3];
ll S[8], ans[8];

struct Segtree{ 
	vector<ll> tree, cnt;
	int N;

	void clear() {
		N = yy.size();
		tree.clear();
		tree.resize(4 * N + 4);

		cnt.clear();
		cnt.resize(4 * N + 4);
	}

	void update(int node, int start, int end, int left, int right, int val) {
		if (right < start || end < left) return;
		if (left <= start && end <= right) cnt[node] += val;
		else {
			int mid = (start + end) / 2;
			update(node * 2, start, mid, left, right, val);
			update(node * 2 + 1, mid + 1, end, left, right, val);
		}

		if (cnt[node]) tree[node] = yy[end] - yy[start - 1];
		else if (start == end) tree[node] = 0;
		else tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
	
	void update(int left, int right, int val) {
		update(1, 1, N, left, right, val);
	}

	ll query() {
		return tree[1];
	}
} tree;

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

vector<Event> events;

ll calc_area() {
	tree.clear();

	int prev_x = -INF;
	ll ret = 0;

	sort(all(events));

	for (auto &[x, y1, y2, val] : events) {
		if (prev_x != -INF){
			ret += (x - prev_x) * tree.query();
		}

		y1 = lower_bound(all(yy), y1) - yy.begin();
		y2 = lower_bound(all(yy), y2) - yy.begin();

		prev_x = x;

		tree.update(y1 + 1, y2, val);
	}

	return ret;
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		int color;
		char c;

		scanf("%d %d %d %d %c", &x1, &y1, &x2, &y2, &c);
		switch (c) {
			case 'C' : color = 0; break;
			case 'M' : color = 1; break;
			case 'Y' : color = 2; break;
		}

		v[color].emplace_back(x1, y1, x2, y2); 

		yy.emplace_back(y1);
		yy.emplace_back(y2);
	}

	compress(yy);

	for (int i = 1; i < 8; i++) {
		events.clear();

		for (int j = 0; j < 3; j++) {
			if (!(i & (1 << j))) continue;

			for (auto &[x1, y1, x2, y2] : v[j]) {
				events.emplace_back(x1, y1, y2, 1);
				events.emplace_back(x2, y1, y2, -1);
			}
		}

		S[i] = calc_area();
	}
	
	//C, M, CM, Y, CY, MY, CMY
	//C, M, Y, R, G, B, K == C, M, Y, MY, CY, CM, CMY
	//1, 2, 4, 6, 5, 3, 7

	for (int i = 0; i < 8; i++) ans[7 ^ i] = S[7] - S[i];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < i; j++) {
			if ((i & j) == j) ans[i] -= ans[j];
		}
	}
	
	for (int i : {1, 2, 4, 6, 5, 3, 7}) {
		printf("%lld ", ans[i]);
	}
}