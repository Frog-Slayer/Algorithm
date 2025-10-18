#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() { 
	fastio;

	int N, C, W;
	cin >> N >> C >> W;

	vector<int> tree(N);
	int mmax = 0;

	for (int i = 0; i < N; i++) { 
		cin >> tree[i];
		mmax = max(mmax, tree[i]);
	}

	ll ans = 0;

	for (int l = 1; l <= mmax; l++) { 
		ll cost = 0;

		for (int j = 0; j < N; j++) { 
			ll cnt = tree[j] / l;
			ll cut = (tree[j] - 1) / l;

			ll res = cnt * l * W - cut * C;
			if (res > 0) cost += res;
		}

		ans = max(ans, cost);
	}

	cout << ans;

}

