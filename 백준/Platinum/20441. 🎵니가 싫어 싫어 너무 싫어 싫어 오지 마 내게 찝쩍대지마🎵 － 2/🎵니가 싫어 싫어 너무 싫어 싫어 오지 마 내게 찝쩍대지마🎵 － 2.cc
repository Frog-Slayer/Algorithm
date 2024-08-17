#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_COEFF = 1000000;
int L, K;

struct Event {
	int x;
	int y1;
	int y2;
	int val;

	Event() {}
	Event(int _x, int _y1, int _y2, int v) : x(_x), y1(_y1), y2(_y2), val(v) {}

	bool operator<(const Event& e) {
		if (x != e.x) return x < e.x;
		return val > e.val;
	}
};

struct Segtree{
	vector<int> tree, lazy;

	Segtree() {
		tree.resize(4 * MAX_COEFF +4);
		lazy.resize(4 * MAX_COEFF +4);
	}

	void propagate(int node, int start, int end) {
		if (lazy[node]) {
			tree[node] += lazy[node];
			if (start != end) {
				lazy[node * 2] += lazy[node];
				lazy[node * 2 + 1] += lazy[node];
			}
			lazy[node] = 0;
		}
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

	int query(int node, int start, int end, int left, int right) {
		propagate(node, start, end);
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node]; 

		int mid = (start + end) / 2;
		return max(query(node *2 , start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
	}
} tree;

vector<Event> events;

int main() {
	scanf("%d%d", &L, &K);
	
	for (int i = 0; i < K; i++){
		int y1, x1, y2, x2;
		scanf("%d%d%d%d", &y1, &x1, &y2, &x2);

		y1 += L;
		x1 += L;

		if (y1 >= y2 && x1 >= x2) {
			events.emplace_back(x2, y2, y1, 1);
			events.emplace_back(x1 + 1, y2, y1, -1);
		}
	}
	
	sort(events.begin(), events.end());

	int ans = 0;

	for (int i = 0, j = 0; i < events.size(); i = j) {
		while (events[i].x == events[j].x){
			tree.update(1, 0, MAX_COEFF, events[j].y1, events[j].y2, events[j].val);
			j++;
		}

		ans = max(ans, tree.query(1, 0, MAX_COEFF, 0, MAX_COEFF));
	}

	printf("%d", ans);
}