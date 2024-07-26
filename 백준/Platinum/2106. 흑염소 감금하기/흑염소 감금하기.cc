#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

const int MAX_Y = 500000;
int N;
vector<tuple<int, int, int, bool>> v;
vector<int> yy;
int tree[4 * MAX_Y], lazy[4 * MAX_Y];

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
	if (left <= start && end <= right){
		lazy[node] += val;
		propagate(node, start, end);
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, left, right, val);
	update(node * 2 + 1, mid + 1, end, left, right, val);

	tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

void update(int left, int right, int val) {
	update(1, 0, MAX_Y - 1, left, right, val);
}

int main(){
	scanf("%d", &N);
	
	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		
		v.emplace_back(x1, y1, y2, false);
		v.emplace_back(x2, y1, y2, true);
		yy.push_back(y1);
		yy.push_back(y2);
	}

	sort(v.begin(), v.end());
	sort(yy.begin(), yy.end());
	yy.erase(unique(yy.begin(), yy.end()), yy.end());

	int max_fence = 0, fence_count = 0;

	for (int i = 0; i < 2 * N; i++) {
		int x, y1, y2;
		bool is_close;
		tie(x, y1, y2, is_close) = v[i];
		y1 = lower_bound(yy.begin(), yy.end(), y1) - yy.begin();
		y2 = lower_bound(yy.begin(), yy.end(), y2) - yy.begin() - 1;

		update(y1, y2, is_close? -1 : 1);

		propagate(1, 0, MAX_Y - 1);
		int q = tree[1]; 

		if (q > max_fence) {
			max_fence = q;
			fence_count = 0;
		}

		if (q == max_fence && !is_close) fence_count++;
	}
	
	printf("%d %d", max_fence, fence_count);
}