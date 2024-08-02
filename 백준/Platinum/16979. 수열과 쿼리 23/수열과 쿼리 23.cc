#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
using namespace std;

typedef long long ll;
int N, M;
vector<tuple<int, int, int>> queries;
vector<int> A, aa, tree;

ll cur;
vector<ll> ans;

void update(int i, int val){
	while (i < tree.size()) {
		tree[i] += val;
		i += (i & -i);
	}
}

ll query(int i) {
	ll ret = 0;
	while (i) {
		ret += tree[i];
		i -= (i & -i);
	}
	
	return ret;
}

ll query(int l, int r) {
	return query(r) - query(l - 1);
}

void expand(int idx, bool is_right) {
	idx = A[idx];

	ll count = is_right ? query(idx + 1, tree.size() - 1) : query(1, idx - 1);
	cur += count;

	update(idx, 1);
}

void shrink(int idx, bool is_right) {
	idx = A[idx];

	ll count = is_right ? query(idx + 1, tree.size() - 1) : query(1, idx - 1);
	cur -= count;

	update(idx, - 1);
}

int main() {
	scanf("%d%d", &N, &M);
	A.resize(N + 1);
	ans.resize(M);

	for (int ai, i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
		aa.emplace_back(A[i]);
	}

	sort(aa.begin(), aa.end());
	aa.erase(unique(aa.begin(), aa.end()), aa.end());
	
	for (int i = 1; i <= N; i++) A[i] = lower_bound(aa.begin(), aa.end(), A[i]) - aa.begin() + 1;

	tree.resize(aa.size() + 1);

	for (int s, e, i = 0; i < M; i++) {
		scanf("%d%d", &s, &e);
		queries.emplace_back(i, s ,e);
	}

	int k = sqrt(N);

	sort(queries.begin(), queries.end(), [k](auto &q1, auto &q2) {
			auto &[i, s1, e1] = q1;
			auto &[j, s2, e2] = q2;
			if (s1/k == s2/k) return e1 < e2;
			return s1/k < s2/k;
			});

	auto [idx, start, end] = queries[0];
	int left = start, right = end;

	for (int i = start; i <= end; i++) expand(i, true);
	ans[idx] = cur;

	for (int i = 1; i < M; i++) {
		tie(idx, start, end) = queries[i];

		while (start < left) expand(--left, false);
	
		while (start > left) shrink(left++, false);

		while (end < right) shrink(right--, true);

		while (end > right) expand(++right, true); 
		
		ans[idx] = cur;
	}
	
	for (ll a : ans) printf("%lld\n", a);
}