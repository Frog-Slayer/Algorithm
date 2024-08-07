#include <iostream>
#include <vector>
using namespace std;

const int INF = 5 * 1e5;
int N, k, d;

struct Segtree{
	vector<int> tree;
	int size;

	Segtree() {}

	Segtree(int sz) {
		size = sz;
		tree.resize(4 * sz + 4);
	}

	void update(int node, int start, int end, int left, int right, int val) {
		if (right < start || end < left) return;
		if (start == end) {
			tree[node] = val;
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, val);
		update(node * 2 + 1, mid + 1, end, left, right, val);

		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	
	}

	void update(int left, int right, int val) {
		update(1, 0, size, left, right, val);
	}

	int query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node];
	
		int mid = (start + end) / 2;
		return max(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
	}

	int query(int left, int right) {
		return query(1, 0, size, left, right);
	}
} sumtree, modtree;

int main() {
	scanf("%d%d%d", &N, &k, &d);

	sumtree = Segtree(INF);
	modtree = Segtree(k);

	int ans = 0;

	for (int i = 1; i <= N; i++){
		int bean;
		scanf("%d", &bean);

		int mod = bean % k;
		
		int q = max(sumtree.query(max(0, bean - d), min(INF, bean + d)), modtree.query(mod, mod)) + 1;

		ans = max(ans, q);

		sumtree.update(bean, bean, q);
		modtree.update(mod, mod, q);
	}

	printf("%d", ans);


}