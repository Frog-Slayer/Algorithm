#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int M, N;

struct Point{
	int idx;
	int x;
	int y;
	int left, right;

	Point(int i, int _x, int _y) : idx(i), x(_x), y(_y) {}
};

struct Segtree{
	vector<int> tree;

	void resize(int M) {
		tree.resize(4 * M + 4);
	}

	void update(int node, int start, int end, int left, int right, int val) {
		if (right < start || end < left) return;
		if (start == end) {
			tree[node] += val;
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, val);
		update(node * 2 + 1, mid + 1, end, left, right, val);

		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	int query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;

		return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
	}
} segtree;

struct Event{
	int idx;
	int val;
	int left, right;
	int y;

	Event(int i, int v, int x1, int x2, int yy) : idx(i), val(v), left(x1), right(x2), y(yy) {}

	bool operator<(const Event& rhs) {
		if (y == rhs.y) return val > rhs.val;
		return y < rhs.y;
	}
};

vector<Point> v;
vector<Event> e;
vector<int> ans;

int main() {
	scanf("%d%d", &M, &N);
	segtree.resize(M);
	ans.resize(N);

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		v.emplace_back(i, x, y);
		e.emplace_back(i, 0, x, x, y);
	}

	//sort by y
	sort(v.begin(), v.end(), [](Point &p1, Point &p2) {
			if (p1.y == p2.y) return p1.x < p2.x;
			return p1.y < p2.y;
			});

	for (int i = 0; i < N; i++) {
		v[i].left = (i == 0 || v[i].y != v[i - 1].y) ? 0 : v[i - 1].x;
		v[i].right = (i == N - 1 || v[i].y != v[i + 1].y) ? M : v[i + 1].x;
	}
	
	sort(v.begin(), v.end(), [](Point &p1, Point &p2) {
			if (p1.x == p2.x) return p1.y < p2.y;
			return p1.x < p2.x;
			});

	for (int i = 0; i < N; i++) {
		e.emplace_back(v[i].idx, -1, v[i].left + 1, v[i].right - 1, (i == 0 || v[i].x != v[i - 1].x) ? 0 : v[i - 1].y);
		e.emplace_back(v[i].idx, 1, v[i].left + 1, v[i].right - 1, (i == N - 1 || v[i].x != v[i + 1].x) ? M : v[i + 1].y);
	}

	sort(e.begin(), e.end());

	for (Event &event : e) {
		if (!event.val) segtree.update(1, 0, M, event.left, event.right, 1);
		else if (event.val < 0) ans[event.idx] -= segtree.query(1, 0, M, event.left, event.right);
		else ans[event.idx] += segtree.query(1, 0, M, event.left, event.right);
	}

	for (int &a : ans) printf("%d\n", a);
}