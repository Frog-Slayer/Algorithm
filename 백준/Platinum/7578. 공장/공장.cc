#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<int, int> A;

struct Fenwick{
	vector<int> tree;
	int N;

	void resize(int _N) {
		N = _N;
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

} tree;

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int a;
		scanf("%d", &a);
		A[a] = i + 1;
	}

	tree.resize(N);

	long long ans = 0;
	for (int i = 0; i < N; i++) {
		int b;
		scanf("%d", &b);
		b = A[b];
		ans += tree.query(N) - tree.query(b);
		tree.update(b, 1);
	}

	printf("%lld", ans);
}