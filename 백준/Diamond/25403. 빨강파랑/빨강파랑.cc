#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(x) sort(all(x)); x.erase(unique(all(x)), x.end())

int N, M, W, H;
vector<tuple<int, int, int>> p;
vector<int> yy;

struct Event {
	int x;
	int y1, y2;
	int val;

	Event(int _x, int _y1, int _y2, int _val) : x(_x), y1(_y1), y2(_y2), val(_val) {}

	bool operator<(const Event& e) {
		if (x == e.x) return val < e.val;
		return x < e.x;
	}
};

struct Segtree{
	vector<pair<int, int>> mn, mx;
	vector<int> lazy;
	int N;

	void resize(int _N) {
		N = _N;
		mn.resize(N * 4);
		mx.resize(N * 4);
		lazy.resize(N * 4);
		set_index(1, 0, N - 1);
	}

	void set_index(int node, int start, int end) {
		if (start == end){
			mn[node].second = mx[node].second = start;
			return;
		}

		int mid = (start + end) / 2;

		set_index(node * 2, start, mid);
		set_index(node * 2 + 1, mid + 1, end);

		mn[node].second = mx[node].second = min({mn[node * 2].second, mn[node * 2 + 1].second}); 
	}

	void propagate(int node, int start, int end) {
		mx[node].first += lazy[node];
		mn[node].first += lazy[node];
		if (start != end) {
			for (int next : { node * 2, node * 2 + 1}) {
				lazy[next] += lazy[node];
			}
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

		int mid = start + end >> 1;

		update(node * 2, start, mid, left, right, val);
		update(node * 2 + 1, mid + 1, end, left, right, val);

		mx[node] = max(mx[node * 2], mx[node * 2 + 1]);
		mn[node] = min(mn[node * 2], mn[node * 2 + 1]);
	}

	void update(int left, int right, int val) {
		update(1, 0, N - 1, left, right, val);
	}

	pair<int, int> query(){
		propagate(1, 0, N - 1);
		if (abs(mx[1].first) > abs(mn[1].first)) return { abs(mx[1].first), mx[1].second };
		return { abs(mn[1].first), mn[1].second };
	}

} tree;

vector<Event> events;

int main() {
	scanf("%d%d%d%d", &N, &M, &W, &H);

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		p.emplace_back(x, y, 1);
		yy.emplace_back(y);
	}

	for (int i = 0; i < M; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		p.emplace_back(x, y, -1);
		yy.emplace_back(y);
	}

	for (auto &[x, y, color] : p) {
		events.emplace_back(x, y, y + H, color);
		events.emplace_back(x + W + 1, y, y + H, -color);
		yy.emplace_back(y + H);
	}

	compress(yy);

	sort(all(events));
	tree.resize(yy.size());

	int ans = 0, ansx = 0, ansy = 0;

	for (int i = 0, j = 0; i < events.size(); i = j) {
		while (j < events.size() && events[j].x == events[i].x) {
			auto &[x, y1, y2, val] = events[j];
			y1 = lower_bound(all(yy), y1) - yy.begin();
			y2 = lower_bound(all(yy), y2) - yy.begin();
			tree.update(y1, y2, val);
			j++;
		}

		pair<int, int> q = tree.query();
		if (q.first > ans) {
			ans = q.first;
			ansx = events[i].x - W;
			ansy = yy[q.second] - H;
		}
	}

	printf("%d\n", ans);
	printf("%d %d", ansx, ansy);
}