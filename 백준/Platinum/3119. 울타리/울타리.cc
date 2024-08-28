#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()

struct Event{
	int x;
	int h;
	int idx;
	int e;
	int v;

	Event(int _x, int _h, int _idx, int _e, int _v) : x(_x), h(_h), idx(_idx), e(_e), v(_v) {}

	bool operator<(const Event &ev) {
		if (x != ev.x) return x < ev.x;
		if (v != ev.v) return v > ev.v;
		if (h != ev.h) return h > ev.h;
		if (e != ev.e) return e > ev.e;
		return idx < ev.idx;
	}
};

struct Node {
	int end;
	int height;
	int idx;

	Node() {}
	Node(int _end, int _height, int _idx) : end(_end), height(_height), idx(_idx) {}

	bool operator< (const Node& n) const {
		return tie(height, end, idx) < tie(n.height, n.end, n.idx);
	}
};

vector<Event> events;

struct Segtree {
	vector<Node> tree;
	int N;

	void resize(int _N) {
		N = _N;
		tree.resize(4 * N + 4);
	}

	void update(int node, int start, int end, int left, int right, Node nd) {
		if (right < start || end < left) return;
		if (start == end) {
			tree[node] = nd;
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, nd);
		update(node * 2 + 1, mid + 1, end, left, right, nd);
		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}

	void update(int idx, Node nd) {
		update(1, 1, N, idx, idx, nd);
	}

	Node query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return { 0, 0, 0 };
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return max(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
	}

	Node query() {
		return tree[1];	
	}

	Node query(int idx) {
		return query(1, 1, N, idx, idx);
	}
} visible, invisible;

int main() {
	int N;
	scanf("%d", &N);
	visible.resize(N);
	invisible.resize(N);

	for (int i = 1; i <= N; i++) {
		int x, w, h;
		scanf("%d%d%d", &x, &w, &h);
		events.emplace_back(x, h, i, x + w, 1);
		events.emplace_back(x + w, h, i, x + w, -1);
	}

	sort(all(events));
	vector<int> ans;

	for (int i = 0, j = 0; i < events.size(); i = j) {
		while (j < events.size() && events[j].x == events[i].x) {
			auto &[x, h, i, e, v] = events[j];
			if (v > 0) {
				Node nd = { e, h, i };
				if (visible.query().height < h) visible.update(i, nd);
				else invisible.update(i, nd);
			}
			else {
				if (visible.query(i).height) {
					visible.update(i, {0, 0, h});
					Node vis_max = visible.query(), invis_max = invisible.query();
					if (vis_max.height < invis_max.height) {
						invisible.update(invis_max.idx, {0, 0, h});
						visible.update(invis_max.idx, invis_max);
					}
				}
				else invisible.update(i, { 0, 0, h});
			}
			j++;
		}

		Node q = visible.query();
		if (q.height) ans.push_back(q.idx);

	}

	sort(all(ans));
	ans.erase(unique(all(ans)), ans.end());

	printf("%ld\n", ans.size());
	for (int a : ans) printf("%d ", a);

}