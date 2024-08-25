#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)); v.erase(unique(all(v)), v.end())

const int MOD = 30013;
int N;
vector<tuple<int, int, int, int, int>> rect;
vector<int> xx, yy;

struct Node {
	int len;
	int cnt;

	Node operator+(const Node& rhs) {
		if (len != rhs.len) return max(rhs); 
		return {len, (cnt + rhs.cnt) % MOD};
	}

	Node max(const Node& rhs) {
		if (len < rhs.len) return rhs;
		return *this;
	}
};

struct Segtree {

	vector<Node> tree;
	int N;

	void resize(int _N){
		N = _N;
		tree.resize(N * 4 + 4);
	}

	void update(int node, int start, int end, int left, int right, Node val) {
		if (right < start || end < left) return;
		if (start == end) {
			tree[node] = tree[node] + val;
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, val);
		update(node * 2 + 1, mid + 1, end, left, right, val);

		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	void update(int idx, Node val) {
		update(1, 1, N, idx, idx, val);
	}

	Node query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return {0, 0};
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
	}

	Node query(int left, int right) {
		return query(1, 1, N, left, right);
	}
} tree;

struct Event {
	int x;
	int y;
	int idx;
	bool low;

	Event(int _x, int _y, int _idx, bool _low) : x(_x), y(_y), idx(_idx), low(_low) {}

	bool operator<(const Event &e) {
		return tie(x, y, low) < tie(e.x, e.y, e.low);
	}
};

vector<Event> events;
vector<Node> memo;

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int upper_left, upper_right, lower_left, lower_right;
		scanf("%d%d%d%d", &upper_left, &upper_right, &lower_left, &lower_right);
		rect.emplace_back(upper_left, lower_left, upper_right, lower_right, i);

		xx.emplace_back(upper_left);
		xx.emplace_back(upper_right);

		yy.emplace_back(lower_left);
		yy.emplace_back(lower_right);
	}

	memo.resize(N);

	compress(xx);
	compress(yy);

	tree.resize(yy.size());

	for (auto &[upper_left, lower_left, upper_right, lower_right, idx] : rect) {
		upper_left = lower_bound(all(xx), upper_left) - xx.begin();
		lower_left = lower_bound(all(yy), lower_left) - yy.begin();
		upper_right= lower_bound(all(xx), upper_right) - xx.begin();
		lower_right= lower_bound(all(yy), lower_right) - yy.begin();


		events.emplace_back(upper_left, lower_left, idx, true);
		events.emplace_back(upper_right, lower_right, idx, false);
	}

	sort(all(events));

	for (int i = 0; i < events.size(); i++) {
		auto &[x, y, idx, low] = events[i];

		if (low) {
			Node q = tree.query(0, y - 1);
			memo[idx] = q;
		}
		else {
			Node &q = memo[idx];
			tree.update(y, { q.len + 1, max(q.cnt , 1)});
		}
	}

	printf("%d %d", tree.tree[1].len, tree.tree[1].cnt);

}