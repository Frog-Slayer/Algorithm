#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
using namespace std;

const int MAX_N = 200000;
int N, K;
vector<tuple<int, int, int>> jewels; 
vector<int> xx;
vector<set<int>> color_set;

struct Fenwick{
	vector<int> tree;

	void clear() {
		tree.clear();
		tree.resize(N + 1);
	}

	void update(int idx, int val) {
		while (idx <= N) {
			tree[idx] += val;
			idx += (idx & -idx);
		}
	}

	int query(int idx) {
		int ret = 0;
		while (idx > 0) {
			ret += tree[idx];
			idx -= (idx & -idx);
		}

		return ret;
	}

	int query(int left, int right) {
		return query(right) - query(left - 1);
	}

} tree;

void init() {
	jewels.clear();
	xx.clear();
	tree.clear();

	color_set.clear();
	color_set.resize(K + 1);

	for (int i = 1; i <= K; i++) color_set[i].insert(0), color_set[i].insert(N + 1);
}

void compress(){
	sort(xx.begin(), xx.end());
	xx.erase(unique(xx.begin(), xx.end()), xx.end());

	for (auto &jewel : jewels) {
		auto &[y, x, c] = jewel;
		x = lower_bound(xx.begin(), xx.end(), x) - xx.begin() + 1;
	}
}

int main() {
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d%d", &N, &K);

		init();

		for (int i = 0; i < N; i++) {
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			jewels.emplace_back(y, x, c);
			xx.emplace_back(x);
		}

		sort(jewels.begin(), jewels.end());
		compress();

		int ans = 0;

		for (int j = 0, i = 0; i < N; i = j) {
			while (get<0>(jewels[j]) == get<0>(jewels[i])) j++;

			for (int k = i; k < j; k++) {
				auto &[y, x, c] = jewels[k];
				set<int>::iterator lit, rit, it;

				it = color_set[c].lower_bound(x);//내 밑에 이미 있나? 
				rit = color_set[c].upper_bound(x);//x오른쪽
				lit = prev(it, 1);

				if (*it != x) ans = max(ans, tree.query(*lit + 1, *rit - 1));//내 밑에 없는 경우는 (left, right)
				else {
					ans = max(ans, tree.query(*lit + 1, x - 1));//(left, cur)
					ans = max(ans, tree.query(x + 1, *rit - 1));//(cur, right);
				}
			}

			for (int k = i; k < j; k++) {
				auto &[y, x, c] = jewels[k];
				color_set[c].insert(x);
				tree.update(x, 1);
			}
		}

		for (int c = 1; c <= K; c++) {
			for (auto it = next(color_set[c].begin(), 1); it != color_set[c].end(); it++) {
				ans = max(ans, tree.query(*prev(it, 1) + 1, *it - 1));
			}
		}

		printf("%d\n", ans);
	}
}