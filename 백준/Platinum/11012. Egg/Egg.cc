#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1e5;
int tree[MAX * 4 + 4], lazy[MAX * 4 + 4];

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

void update(int node, int start, int end, int left, int right, int val){
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
}

void update(int left, int right, int val){
	update(1, 0, MAX, left, right, val);
}

int query(int node, int start, int end, int left, int right){
	propagate(node, start, end);

	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

int query(int idx) {
	return query(1, 0, MAX, idx, idx);
}

int main(){
	int T;
	scanf("%d", &T);

	while (T--) {
		vector<int> eggs[MAX + 1];
		vector<pair<int, int>> v_open[MAX + 1], v_close[MAX + 1];

		for (int i = 0; i < MAX * 4 + 4; i++) tree[i] = lazy[i] = 0;

		int n, m;
		scanf("%d%d", &n, &m);

		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			eggs[x].push_back(y);
		}

		for (int i = 0; i < m; i++) {
			int l, r, b, t;
			scanf("%d%d%d%d", &l, &r, &b, &t);
			v_open[l].emplace_back(b, t);
			v_close[r].emplace_back(b, t);
		}

		int ans = 0;

		for (int i = 0; i <= MAX; i++) {
			for (auto open : v_open[i]) {
				update(open.first, open.second, 1);
			}

			for (int egg: eggs[i]) {
				ans += query(egg);
			}

			for (auto close : v_close[i]) {
				update(close.first, close.second, -1);
			}
		}

		printf("%d\n", ans);
	}
}