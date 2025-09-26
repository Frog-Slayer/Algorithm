#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() { 
	fastio;

	int T;
	cin >> T;

	for (int i = 1; i <= T; i++) { 
		ll N, K;
		cin >> N >> K;

		vector<tuple<ll, ll, ll>> coffee;

		for (int j = 0; j < N; j++) { 
			ll c, t, s;
			cin >> c >> t >> s;

			coffee.emplace_back(c, t, s);
		}

		sort(all(coffee), [&](auto &c, auto &k){ 
				auto [c1, t1, s1] = c;
				auto [c2, t2, s2] = k;

				return t1 < t2;
				});

		ll day = 0, ans = 0;
		priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;

		for (int i = 0; i < N; i++) { 
			auto &[c, t, s] = coffee[i];

			ll day_to_add = min(c, t - day);

			c -= day_to_add;
			day += day_to_add;

			pq.emplace(s, day_to_add);

			while (c && !pq.empty()) { 
				auto [sat, input] = pq.top();
				if (sat >= s) break;
				pq.pop();

				ll to_replace = min(c, input);

				c -= to_replace;
				input -= to_replace;

				if (input) pq.emplace(sat, input);
				pq.emplace(s, to_replace);
			}
		}

		while (!pq.empty()) { 
			auto [s, c] = pq.top();
			pq.pop();

			ans += s * c;
		}


		cout << "Case #" << i << ": " << ans << '\n';
	}

}
