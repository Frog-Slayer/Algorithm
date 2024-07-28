#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

const int INF = 2e5;
int T, n, k, l;
vector<tuple<int, int, int, int, int>> v;
vector<tuple<int, bool>> queries;
vector<int> xx, yy, ans;

struct Segtree {
	vector<int> tree;
	int size;
	
	Segtree() {}

	void init(int _size) {
		size = _size;
		tree.clear();
		tree.resize(size * 4);
		fill(tree.begin(), tree.end(), INF);
	}

	void update(int node, int start, int end, int idx, int val) {
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] = min(tree[node], val);
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, idx, val);
		update(node * 2 + 1, mid + 1, end, idx, val);
	
		tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	}

	void update(int idx, int val) {
		update(1, 0, size - 1, idx, val); 
	}

	int query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return INF;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return min(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
	}

	int query(int left, int right) {
		return query(1, 0, size - 1, left, right);
	}

} x_seg, y_seg;

void init() {
	v.clear();
	xx.clear();
	yy.clear();
	queries.clear();
	ans.clear();
}

void compress(){
	sort(xx.begin(), xx.end());
	sort(yy.begin(), yy.end());

	xx.erase(unique(xx.begin(), xx.end()), xx.end());
	yy.erase(unique(yy.begin(), yy.end()), yy.end());
}

void init_queries() {
	x_seg.init(xx.size());
	y_seg.init(yy.size());

	for (int i = 0; i < l; i++) {
		int a;
		bool b;

		tie(a, b) = queries[i];

		if (!b){
			a = lower_bound(yy.begin(), yy.end(), a) - yy.begin();
			y_seg.update(a, i);
		}
		else {
			a = lower_bound(xx.begin(), xx.end(), a) - xx.begin();
			x_seg.update(a, i);
		}
	}
}

void solve() {
	ans.resize(l);

	for (int i = 0; i < v.size(); i++) {
		int x1, y1, x2, y2, w;
		tie(x1, y1, x2, y2, w) = v[i];

		x1 = lower_bound(xx.begin(), xx.end(), x1) - xx.begin();
		x2 = lower_bound(xx.begin(), xx.end(), x2) - xx.begin();
		y1 = lower_bound(yy.begin(), yy.end(), y1) - yy.begin();
		y2 = lower_bound(yy.begin(), yy.end(), y2) - yy.begin();

		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		
		int delete_query_idx = min(x_seg.query(x1, x2), y_seg.query(y1, y2));
		if (delete_query_idx == INF) continue;
		ans[delete_query_idx] = max(ans[delete_query_idx], w);
	}

	for (int i = 0; i < l; i++) {
		printf("%d\n", ans[i]);
	}
}

int main(){
	scanf("%d", &T);
	
	while (T--) {
		init();

		scanf("%d%d%d", &n, &k, &l);

		for (int i = 0; i < k; i++) {
			int x1, y1, x2, y2, w;
			scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &w);
			v.emplace_back(x1, y1, x2, y2, w);
			xx.emplace_back(x1), xx.emplace_back(x2);
			yy.emplace_back(y1), yy.emplace_back(y2);
		}
		
		for (int i = 0; i < l; i++) {
			int a, b;
			scanf("%d%d", &a, &b);

			queries.emplace_back(a, b);

			if (!b) yy.emplace_back(a);	
			else xx.emplace_back(a); 
		}

		compress();
		init_queries();

		solve();
	}
}