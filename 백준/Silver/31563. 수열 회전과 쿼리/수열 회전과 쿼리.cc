#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() { 
	fastio;

	int N, Q;
	cin >> N >> Q;

	int base = 0;
	vector<int> v(N);
	vector<ll> sum(N);

	for (int i = 0; i < N; i++){ 
		cin >> v[i];

		if (!i) sum[i] = v[i];
		else sum[i] = v[i] + sum[i - 1];
	}

	for (int i = 0; i < Q; i++) { 
		int q;
		cin >> q;

		if (q < 3) { 
			int k;
			cin >> k;

			if (q == 1) base = (base + N - k) % N;
			else base = (base + k) % N;
		}
		else {
			int a, b;
			cin >> a >> b;

			a = (a - 1 + base) % N;
			b = (b - 1 + base) % N;

			if (a <= b) cout << sum[b] - (a ? sum[a - 1] : 0) << '\n';
			else cout << sum[N - 1] - (sum[a] - (b ? sum[b - 1] : 0)) + v[a] + v[b] << '\n';
		}

	}
}
