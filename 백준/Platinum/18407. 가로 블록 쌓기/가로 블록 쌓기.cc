#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, xx_size;
vector<int> xx, tree, lazy;
vector<pair<int, int>> blocks;

void propagate(int node, int start, int end) {
	if (lazy[node]) {
		tree[node] = lazy[node];

		if (start != end) {
			lazy[node * 2] = lazy[node];	
			lazy[node * 2 + 1] = lazy[node];
		}

		lazy[node] = 0;	
	}
}

void update(int node, int start, int end, int left, int right, int val) {
	propagate(node, start, end);
	if (right < start || end < left) return;
	if (left <= start && end <= right) {
		lazy[node] = val;
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

void update(int left, int right) {
	int val = query(1, 0, xx_size, left, right);
	update(1, 0, xx_size, left, right, val + 1); 
}

int main(){
	scanf("%d", &N);

	for (int i = 0; i < N; i++){
		int W, D;
		scanf("%d%d", &W, &D);
		W--, D--;
		xx.push_back(D);
		xx.push_back(W + D);
		blocks.emplace_back(D, W + D);
	}

	sort(xx.begin(), xx.end());
	xx.erase(unique(xx.begin(), xx.end()), xx.end());
	xx_size = xx.size();

	tree.resize(xx_size * 4);
	lazy.resize(xx_size * 4);
	
	for (int i = 0; i < N; i++) {
		int s = lower_bound(xx.begin(), xx.end(), blocks[i].first) - xx.begin();
		int e = lower_bound(xx.begin(), xx.end(), blocks[i].second) - xx.begin();

		update(s, e);
	}

	printf("%d", query(1, 0, xx_size, 0, xx_size));
}
