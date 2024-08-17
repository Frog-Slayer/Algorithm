#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAX_Y = 1000000;
int T;
vector<tuple<int, int, int, int>> v;

struct Segtree{
	vector<int> tree, cnt;

	void init() {
		tree.clear();
		tree.resize(4 * MAX_Y + 4);
		cnt.clear();
		cnt.resize(4 * MAX_Y + 4);
	}

	void update(int node, int start, int end, int left, int right, int val) {
		if (right < start || end < left) return;
		if (left <= start && end <= right) {
			cnt[node] += val;
		}
		else {
			int mid = (start + end) / 2;
			update(node * 2, start, mid, left, right, val);
			update(node * 2 + 1, mid + 1, end, left, right, val);
		}

		if (cnt[node]) tree[node] = (end - start + 1);
		else if (start == end) tree[node] = 0; 
		else tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	void update(int left, int right, int val) {
		update(1, 0, MAX_Y, left, right, val);
	}

} tree;


int main() {
	scanf("%d", &T);

	while (T--) {
		int N;
		scanf("%d", &N);

		tree.init();
		v.clear();

		for (int i = 0; i < N; i++) {
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			v.emplace_back(x1, y1, y2, -1);
			v.emplace_back(x2, y1, y2, 1);
		}


		sort(v.begin(), v.end());

		ll ans = 0;

		for (int i = 0; i < v.size(); i++) {
			if (i) {
				int diff = get<0>(v[i]) - get<0>(v[i - 1]);
				ans += (ll) tree.tree[1] * diff;
			}

			auto &[x, y1, y2, val] = v[i];

			tree.update(y1, y2 - 1, -val);
		}

		printf("%lld\n", ans);
	}
}
