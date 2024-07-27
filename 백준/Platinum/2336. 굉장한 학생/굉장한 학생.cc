#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Score{
	int t1, t2, t3;
	
	bool operator<(const Score &s) {
		return t1 < s.t1;
	}
};

const int INF = 1e6;
const int MAX_N = 5e5 + 1;
int N, n;
int tree[MAX_N * 4];
vector<Score> v;

void update(int node, int start, int end, int idx, int val) {
	if (idx < start || end < idx) return;
	if (start == end) {
		tree[node] = val;
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, idx, val);
	update(node * 2 + 1, mid + 1, end, idx, val);
	tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

void update(int idx, int val) {
	update(1, 1, MAX_N, idx, val);
}

int query(int node, int start, int end, int left, int right) {
	if (right < start || end < left) return INF;
	if (left <= start && end <= right) return tree[node];
	int mid = (start + end) / 2;

	return min(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
}

int query(int left, int right) {
	return query(1, 1, MAX_N, left, right);
}

int main(){
	scanf("%d", &N);
	v.resize(N + 1);
	fill(tree, tree + MAX_N * 4, INF);

	v[0] = {0, 0, 0};

	for (int i = 1; i <= N; i++) {
		scanf("%d", &n);
		v[n].t1 = i;
	}

	for (int i = 1; i <= N; i++) {
		scanf("%d", &n);
		v[n].t2 = i;
	}

	for (int i = 1; i <= N; i++) {
		scanf("%d", &n);
		v[n].t3 = i;
	}

	sort(v.begin(), v.end());

	int ans = 0;

	for (int i = 1; i <= N; i++) {
		if (query(1, v[i].t2 - 1) > v[i].t3) ans++;
		update(v[i].t2, v[i].t3);
	}

	printf("%d", ans);
}