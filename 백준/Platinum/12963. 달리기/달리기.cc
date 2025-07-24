#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;
const ll MOD = 1000000007;

struct UF { 
	vector<int> parent;

	UF(int n) : parent(n) {
		for (int i = 0; i < n; i++) parent[i] = i;
	}

	void merge(int a, int b) { 
		a = find(a), b = find(b);
		parent[a] = b;
	}

	int find(int a) { 
		if (parent[a] == a) return a;
		return parent[a] = find(parent[a]);
	}
};


int main() {
	fastio;

	int N, M;
	cin >> N >> M;

	vector<ll> v(M);
	ll cur = 1;

	for (int i = 0; i < M; i++) { 
		v[i] = cur;
		cur *= 3;
		cur %= MOD;
	}

	vector<pair<int, int>> e(M);

	for (int i = 0; i < M; i++) cin >> e[i].first >> e[i].second;

	UF uf(N);
	ll ans = 0;

	for (int i = M - 1; i >= 0; i--) { 
		int l = uf.find(e[i].first), r = uf.find(e[i].second);
		int start = uf.find(0), end = uf.find(N - 1);

		if ((l == start  && r == end) || (r == start && l == end)) { 
			ans += v[i];
			ans %= MOD;
		}
		else uf.merge(l, r);
	}


	cout << ans;

}
