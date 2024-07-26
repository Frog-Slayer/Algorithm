#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

const int MAX_N = 20000;
vector<tuple<int, int, int>> v;

int K, N, C;
int tree[MAX_N * 4 + 4], lazy[MAX_N * 4 + 4];

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

	return max(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
}

int main(){
	scanf("%d%d%d", &K, &N, &C);

	for (int i = 0; i < K; i++) {
		int s, e, m;
		scanf("%d%d%d", &s, &e, &m);
		v.emplace_back(e, s, m);
	}

	sort(v.begin(), v.end());

	int ans = 0;
	for (int i = 0; i < K; i++) {
		auto [e, s, m] = v[i];

		int q = min(C - query(1, 1, N, s, e - 1), m); 
		//printf("max(%d %d) = %d\n", s, e, q);
		update(1, 1, N, s, e - 1, q);
		ans += q;
	}

	printf("%d", ans);
}