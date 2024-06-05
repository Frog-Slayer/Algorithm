#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define LEFT_CHILD node * 2
#define RIGHT_CHILD node * 2 + 1

const int MAX_N = 2e5;

int N;
vector<int> yy;
vector<pair<int, int>> ys;//first: in, second: out
int tree[MAX_N * 4], lazy[MAX_N * 4];

void propagate(int node, int start, int end) {
	if (lazy[node]) {
		tree[node] += lazy[node];
		if (start != end) {
			lazy[LEFT_CHILD] += lazy[node];
			lazy[RIGHT_CHILD] += lazy[node];
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
	update(LEFT_CHILD, start, mid, left, right, val); 
	update(RIGHT_CHILD, mid + 1, end, left, right, val); 
	tree[node] = max(tree[LEFT_CHILD], tree[RIGHT_CHILD]);
}

int query(int node, int start, int end, int left, int right) {
	propagate(node, start, end);
	
	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;

	return max(query(LEFT_CHILD, start, mid, left, right), query(RIGHT_CHILD, mid + 1, end, left, right)); 
}

int main(){
	scanf("%d", &N);

	for (int i = 0; i < N; i++){
		int ux, uy, vx, vy;
		scanf("%d%d%d%d", &ux, &uy, &vx, &vy);//uy > vy
		yy.push_back(vy);
		yy.push_back(uy);
		ys.emplace_back(vy, uy);
	}
	
	// compress
	sort(yy.begin(), yy.end());
	yy.erase(unique(yy.begin(), yy.end()), yy.end());

	for (int i = 0; i < N; i++){
		int lb = lower_bound(yy.begin(), yy.end(), ys[i].first) - yy.begin();
		ys[i].first = lb;

		lb = lower_bound(yy.begin(), yy.end(), ys[i].second) - yy.begin();
		ys[i].second = lb;

		update(1, 0, MAX_N - 1, ys[i].first, ys[i].second, 1);
	}

	sort(ys.begin(), ys.end());

	int ans = 0;
	vector<int> tmp;

	for (int i = 0; i < MAX_N; i++) {
		tmp.push_back(query(1, 0, MAX_N - 1, i, i));
	}

	int j = 0;
	for (int i = 0; i < MAX_N; i++) {//위쪽
		for (; j < N && ys[j].first <= i; j++) {
			update(1, 0, MAX_N - 1, ys[j].first, ys[j].second, -1);	
		}

		ans = max(ans, tmp[i] + query(1, 0, MAX_N - 1, 0, MAX_N - 1));
	}

	printf("%d", ans);

}