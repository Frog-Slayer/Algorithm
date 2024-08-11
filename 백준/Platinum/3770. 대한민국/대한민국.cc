#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, N, M, K;
vector<pair<int, int>> v;

struct Segtree{
	vector<int> tree;

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

	void clear_and_resize(int N) {
		tree.clear();
		tree.resize(4* N + 4);
	}

}tree;

int main(){
	scanf("%d", &T);

	for (int t = 1; t <= T; t++) {
		v.clear();
		scanf("%d%d%d", &N, &M, &K);

		for (int i = 0; i < K; i++) {
			int east, west;
			scanf("%d%d", &east, &west);
			v.emplace_back(east, west);
		}

		sort(v.begin(), v.end());
		
		tree.clear_and_resize(M);

		long long ans = 0;

		for (int i = 0; i < K; i++) {
			int east = v[i].first, west = v[i].second;
			ans += tree.query(1, 1, M, west + 1, M);
			tree.update(1, 1, M, west, west, 1);
		}

		printf("Test case %d: %lld\n", t, ans);

	}
}