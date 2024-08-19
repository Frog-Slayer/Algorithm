#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
using namespace std;
#define all(v) v.begin(), v.end()

int N, Q;
vector<tuple<int, int, int, int>> queries;
vector<int> ans, ss;

struct Score{
	int sum;
	int s;
	int t;

	Score (int _s, int _t) : s(_s), t(_t), sum(_s + _t) {} 

	bool operator<(const Score& rhs) {
		return sum > rhs.sum;
	}
};

vector<Score> v;

struct FenwickMS{

	vector<multiset<int>> tree;
	int N;
	
	void resize(int _N) {
		N = _N;
		tree.resize(N + 1);
	}

	void update(int idx, int val) {
		while (idx <= N) {
			tree[idx].insert(val);
			idx += (idx & -idx);
		}
	}

	int query(int idx, int val) {
		int ret = 0;
		while (idx > 0) {
			ret += tree[idx].size() - distance(tree[idx].begin(), tree[idx].lower_bound(val));
			idx -= (idx & -idx);
		}
		return ret;
	}

	int query(int left, int right, int val) {
		return query(right, val) - query(left - 1, val);
	}

} tree;

void compress(){
	sort(all(ss));
	ss.erase(unique(all(ss)), ss.end());

	tree.resize(ss.size());
}

int main() {
	scanf("%d%d", &N, &Q);

	ans.resize(Q);

	for (int i = 0; i < N; i++) {
		int s, t;
		scanf("%d%d", &s, &t);
		v.emplace_back(s, t);
		ss.emplace_back(s);
	}

	compress();

	for (int i = 0; i < Q; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		queries.emplace_back(z, x, y, i);
	}
	
	sort(all(v));
	sort(all(queries), greater<>());

	for (int j = 0, i = 0; i < Q; i++) {
		auto &[sum, s, t, idx] = queries[i];

		while (j < N && v[j].sum >= sum) {
			int s = lower_bound(all(ss), v[j].s) - ss.begin() + 1;
			int t = v[j].t;
			tree.update(s, t);
			j++;
		}
	
		s = lower_bound(all(ss), s) - ss.begin() + 1;
		ans[idx] = tree.query(s, ss.size(), t);
	}

	for (int i = 0; i < Q; i++) printf("%d\n", ans[i]);
}
