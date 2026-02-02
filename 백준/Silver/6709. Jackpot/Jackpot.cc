#include <iostream>
#include <vector>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)

typedef long long ll;

ll gcd(ll a, ll  b) { 
	while (b) { 
		ll r = a % b;
		a = b;
		b = r;
	}

	return a;
}

ll lcm(vector<ll> &v) { 
	ll ret = v[0];

	for (auto &n : v) { 
		ret = ret * n / gcd(ret, n);
	}

	return ret;
}

int main () { 
	fastio;

	int T;
	cin >> T;

	while (T--) { 
		int n;
		cin >> n;

		vector<ll> v(n);

		for (int i = 0; i < n; i++) cin >> v[i]; 

		ll d = lcm(v);

		if (d <= 1e9) cout << d << '\n';
		else cout << "More than a billion.\n";
	}
}