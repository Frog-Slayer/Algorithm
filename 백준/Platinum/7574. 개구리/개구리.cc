#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

const int MAX_N = 100000;	
const int MAX_Y = 10000001;
int N, r, d;
int parent[MAX_N + 1];
vector<int> tree, lazy, yy;
vector<pair<int, int>> v;
set<int> s;

int find(int a){ 
	if (parent[a] == a) return a;
	return parent[a] = find(parent[a]);
}

void uni(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return;
	parent[a] = b;
}

void propagate(int node, int start, int end) {
	if (lazy[node]) {
		tree[node] = max(tree[node], lazy[node]);
		if (start != end) {
			lazy[node * 2] = max(lazy[node * 2], lazy[node]);	
			lazy[node * 2 + 1] = max(lazy[node * 2 + 1], lazy[node]);
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

void update(int left, int right, int val) {
	update(1, 0, yy.size() - 1, left, right, val);
}

int get_compressed_y(int y){
	return lower_bound(yy.begin(), yy.end(), y) - yy.begin();
}

void query(int node, int start, int end, int left, int right) {
	propagate(node, start, end);
	if (right < start || end < left) {
		s.insert(0);
		return;
	}
	if (left <= start && end <= right) {
		s.insert(tree[node]);
		return;
	}

	int mid = (start + end) / 2;
	query(node * 2, start, mid, left, right);
	query(node * 2 + 1, mid + 1, end, left, right);
}

void query(int left, int right) {
	query(1, 0, yy.size() - 1, left, right);
}

int main(){
	scanf("%d%d", &N, &r);

	for (int i = 1; i <= N; i++) {
		int x, y;
		parent[i] = i;
		scanf("%d%d", &x, &y);
		v.emplace_back(x, y);
	}

	scanf("%d", &d);

	for (int i = 0; i < N; i++) {
		int y = v[i].second;
		yy.emplace_back(y);
		yy.emplace_back(y + r);
		yy.emplace_back(max(y - d, 0));
		yy.emplace_back(min(y + r + d, MAX_Y - 1));
	}

	sort(yy.begin(), yy.end());
	yy.erase(unique(yy.begin(), yy.end()), yy.end());

	tree.resize(yy.size() * 4);
	lazy.resize(yy.size() * 4);

	sort(v.begin(), v.end());

	for (int i = 1; i <= N; i++) {
		int x = v[i - 1].first, y = v[i - 1].second;
	
		int left = max(x - d, 0);
		int upper = y + r;
		int bottom = max(y -d , 0);
		int top = min(y + r + d, MAX_Y);

		bottom = get_compressed_y(bottom);
		y = get_compressed_y(y);
		upper = get_compressed_y(upper);
		top = get_compressed_y(top);

		s.clear();
		query(bottom, y); 

		for (int q : s) {
			if (q && v[q - 1].first + r >= x) uni(q, i);
		}

		s.clear();
		query(y, upper);

		for (int q : s) {
			if (q && v[q - 1].first + r >= left) uni(q, i);
		}

		s.clear();
		query(upper, top); 

		for (int q : s) {
			if (q && v[q - 1].first + r >= x) uni(q, i);
		}

		update(y, upper, i);
	}
	
	int max_sum = 0;

	for (int i = 1; i <= N; i++) {
		if (find(i) == find(1)) {
			max_sum = max(max_sum, v[i - 1].first + v[i - 1].second);
		}
	}

	printf("%d", max_sum + 2 * r);

}