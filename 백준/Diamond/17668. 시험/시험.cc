#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
using namespace std;
#define all(v) v.begin(), v.end()

const int MAX = 1e9;
int N, Q;
vector<tuple<int, int, int, int>> queries;
vector<int> ans, ss;
map<int, vector<int>> m;

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

struct Multidimensional_Segtree{
	int N;
	vector<vector<int>> tree;
	vector<vector<int>> v;
	
	void resize() {
		N = ss.size();
		tree.resize(N + 1);
		v.resize(N + 1);

		int idx = 1;

		for (auto p : m) {
			for (int t : p.second) {
				for (int i = idx; i <= N; i += (i & -i)) {
					v[i].emplace_back(t);
				}
			}

			idx++;
		}

		for (int i = 1; i <= N; i++) {
			tree[i].resize(v[i].size() + 1);
			sort(v[i].begin(), v[i].end());
		}
	}

	void update(int x, int y) {
		for (int xx = upper_bound(all(ss), x) - ss.begin(); xx <= N; xx += (xx & -xx)) {
			for (int yy = upper_bound(all(v[xx]), y) - v[xx].begin(); yy <= v[xx].size(); yy += (yy & -yy)) {
				tree[xx][yy]++;
			}
		}
	}

	int q(int x, int y) {
		int ret = 0;

		for (int xx = upper_bound(all(ss), x) - ss.begin(); xx > 0; xx -= (xx & -xx)) {
			for (int yy = upper_bound(all(v[xx]), y) - v[xx].begin(); yy > 0; yy -= (yy & -yy)) {
				ret += tree[xx][yy];
			}
		}

		return ret;
	}

	int query(int x, int y) {
		return q(MAX, MAX) - q(MAX, y - 1) - q(x - 1, MAX) + q(x - 1, y - 1);
	}

} tree;

void compress(){
	sort(all(ss));
	ss.erase(unique(all(ss)), ss.end());
	tree.resize();
}

int main() {
	scanf("%d%d", &N, &Q);

	ans.resize(Q);

	for (int i = 0; i < N; i++) {
		int s, t;
		scanf("%d%d", &s, &t);
		v.emplace_back(s, t);
		ss.emplace_back(s);
		m[s].emplace_back(t);
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
			tree.update(v[j].s, v[j].t);
			j++;
		}
	
		ans[idx] = tree.query(s, t);
	}

	for (int i = 0; i < Q; i++) printf("%d\n", ans[i]);
}