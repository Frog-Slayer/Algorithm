#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)); v.erase(unique(all(v)), v.end())
#define compressed(x) lower_bound(all(xx), x) - xx.begin()

typedef tuple<int, bool, int> Event;
typedef tuple<int, int, int, int, int> Wall;
typedef tuple<int, int, int> Laser;

const int INF = 2e5;
vector<int> xx;
vector<Wall> walls;
vector<Laser> laser;
priority_queue<Event, vector<Event>, greater<>> events;

vector<priority_queue<int, vector<int>, greater<>>> pq;
vector<vector<int>> ans;

struct Node {
	int idx;
	int val;

	Node() { idx = -1; val = INF; }
	Node(int _idx, int _val) : idx(_idx), val(_val) {}

	Node operator+(const Node& nd) {
		if (val < nd.val) return *this;
		return nd; 
	}
};

struct Segtree {
	int N;
	vector<Node> tree;

	void resize(int _N) {
		N = _N;
		tree.resize(4 * N + 4);
	}

	void update(int node, int start, int end, int idx, int val) {
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] = { idx, val };
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, idx, val);
		update(node * 2 + 1, mid + 1, end, idx, val);

		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	void update(int idx, int val) {
		update(1, 0, N, idx, val);
	}

	Node query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return { -1, INF };
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		Node l = query(node * 2, start, mid, left, right);
		Node r = query(node * 2 + 1, mid + 1, end, left, right);
		return l + r;
	}

	Node query(int left, int right) {
		return query(1, 0, N, left, right);
	}
} tree;

int main() {
	int N, Q;

	scanf("%d%d", &N, &Q);

	walls.resize(N);
	laser.resize(Q);
	ans.resize(Q);

	for (int i = 0; i < N; i++) {
		int l, r, h, v;
		scanf("%d%d%d%d", &l, &r, &h, &v);
		xx.emplace_back(l);
		xx.emplace_back(r);
		xx.emplace_back(v);

		walls[i] = { h, l, r, v, i };
	}

	for (int i = 0; i < Q; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		xx.emplace_back(x);
		laser[i] = { y, x, i };
	}

	compress(xx);
	pq.resize(xx.size());
	tree.resize(xx.size());

	for (auto &[h, l, r, v, i] : walls) {
		l = compressed(l);
		r = compressed(r);
		v = compressed(v);
		events.push({h, true, i});
	}

	for (auto &[y, x, i] : laser) {
		x = compressed(x);
		events.push({y, false, i});
	}

	while (!events.empty()) {
		auto &[y, is_wall, idx] = events.top();

		if (!is_wall) {
			int x = get<1>(laser[idx]);
			pq[x].push(idx);
			tree.update(x, pq[x].top());
		}
		else {
			int x = get<1>(laser[idx]);
			auto &[h, l, r, v, i] = walls[idx];
			Node hit = tree.query(l, r);

			if (hit.val != INF) {
				pq[hit.idx].pop();

				if (pq[hit.idx].empty()) tree.update(hit.idx, INF);
				else tree.update(hit.idx, pq[hit.idx].top());

				ans[hit.val].push_back(idx);

				get<1>(laser[hit.val]) = v;
				events.push({y + 1, false, hit.val});
			}
		}
		events.pop();
	}

	for (int i = 0; i < Q; i++) {
		int sz = ans[i].size();
		printf("%d\n", sz);

		if (sz) {
			for (int &a :ans[i]) printf("%d ", a + 1);
			printf("\n");
		}
	}
}