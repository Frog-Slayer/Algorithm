#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int T, M;

vector<int> tree, lazy;
vector<vector<pair<int, int>>> v;
vector<tuple<int, int, int, int>> vv;
vector<int> xx, yy;

void init() {
	tree.clear();
	lazy.clear();
	v.clear();
	vv.clear();
	xx.clear();
	yy.clear();
}

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

	update(node * 2, start ,mid, left, right, val);
	update(node * 2 + 1, mid + 1, end, left, right, val);

	tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

void update(int left, int right, int val) {
	update(1, 0, xx.size(), left, right, val);
}

int query(int node, int start, int end, int left, int right) {
	propagate(node, start, end);
	if (right < start || end < left) return 0;

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;

	return max(query(node * 2, start ,mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
}

int query(int left, int right) {
	return query(1, 0, xx.size(), left, right);
}

int main(){
	scanf("%d", &T);

	while (T--) {
		init();
		scanf("%d", &M);
		v.resize(M);

		for (int i = 0; i < M; i++) {
			int k;
			scanf("%d", &k);

			for (int j = 0; j < k; j++) {
				int x, y;
				scanf("%d%d", &x, &y);
				v[i].emplace_back(x, y);
				xx.push_back(x);
				yy.push_back(y);
			}
		}

		sort(xx.begin(), xx.end());
		xx.erase(unique(xx.begin(), xx.end()), xx.end());
		sort(yy.begin(), yy.end());
		yy.erase(unique(yy.begin(), yy.end()), yy.end());

		tree.resize(yy.size());
		lazy.resize(yy.size());

		for (int i = 0; i < yy.size(); i++) {
			tree.resize(xx.size() * 4);
			lazy.resize(xx.size() * 4);
		}

		for (int i = 0; i < M; i++) {
			for (int j = 0; j < v[i].size(); j++) {
				pair<int, int> &p = v[i][j];
				//압축 
				int comp_x = lower_bound(xx.begin(), xx.end(), p.first) - xx.begin();
				int comp_y = lower_bound(yy.begin(), yy.end(), p.second) - yy.begin();

				p = {comp_x, comp_y};
			}

			for (int j = 0; j < v[i].size(); j++) {
				pair<int, int> &cur = v[i][j];
				pair<int, int> &prev = v[i][(j - 1 + v[i].size()) % v[i].size()];

				if (prev.second != cur.second) continue;
				
				if (prev.first < cur.first){//open
					vv.emplace_back(prev.second, prev.first, cur.first - 1, -1);
				}
				else {//close
					vv.emplace_back(prev.second, cur.first, prev.first - 1, 1);
				}
			}
		}

		sort(vv.begin(), vv.end());

		int ans = 0;
		for (int i = 0; i < vv.size(); i++) {
			auto [y, start, end, val] = vv[i];
			update(start, end, -val);
			ans = max(ans, query(0, xx.size()));
		}

		printf("%d\n", ans);
	}
}