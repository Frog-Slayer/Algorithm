#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()
#define fastio cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false)

const int MAX_NM = 300000;
typedef __int128_t ll;

vector<vector<int>> member(MAX_NM + 1);
vector<int> goal(MAX_NM + 1);

struct Fenwick {
	int N;
	vector<ll> tree;

	Fenwick(int _N): N(_N), tree(_N + 1) {}

	ll sum(int i) {
		ll ret = 0;
		while (i > 0) {
			ret += tree[i];
			i -= (i & -i);
		}

		return ret;
	}

	void add(int i, int val) {
		while (i <= N){
			tree[i] += val;
			i += (i & -i);
		}
	}

	void range_upd(int left, int right, int val) {
		add(left, val);
		add(right + 1, -val);
	}
};

int main() {
	fastio;
	int N, M;

	cin >> N >> M;

	for (int i = 1; i <= M; i++) {
		int o;
		cin >> o;
		member[o].emplace_back(i);
	}
	for (int i = 1; i <= N; i++) cin >> goal[i];

	vector<tuple<int, int, int>> queries;
	int Q;
	cin >> Q;

	for (int i = 0; i < Q; i++) {
		int l, r, a;
		cin >> l >> r >> a;
		queries.emplace_back(l, r, a);
	}

	vector<pair<int, int>> pbs(N + 1, make_pair(0, Q));
	vector<int> ans(N + 1, -1);

	int flag = true;

	while (flag) {
		flag = false;
		vector<pair<int, int>> tasks;
		Fenwick tree(M);

		for (int i = 1; i <= N; i++) {
			if (pbs[i].first >= pbs[i].second) continue ;
			tasks.emplace_back(pbs[i].first + pbs[i].second >> 1, i);
			flag = true;
		}

		sort(all(tasks));

		int j = 0;
		for (auto &[m, i]: tasks) {
			while (j <= m) {
				auto &[l, r, a] = queries[j];
				if (l <= r) tree.range_upd(l, r, a);
				else {
					tree.range_upd(l, M, a);
					tree.range_upd(1, r, a);
				}
				j++;
			}

			ll sum = 0;
			for (auto &a : member[i]) sum += tree.sum(a);

			if (sum >= goal[i]) pbs[i].second = m;
			else pbs[i].first = m + 1;
		}
	}

	for (int i = 1; i <= N; i++) {
		if (pbs[i].first == Q) cout << "NIE\n";
		else cout << pbs[i].first + 1 << '\n';
	}
}