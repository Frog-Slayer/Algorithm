#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

const int MAX_N = 100000;

vector<ll> sum(MAX_N + 1, 0), dp(MAX_N + 1, 0);

int main() { 
	fastio;

	int N, K;
	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		int e;
		cin >> e;
		sum[i] = sum[i - 1] + e;
	}

	priority_queue<pair<ll, ll>> pq;

	for (int i = 1; i <= N; i++) { 
		ll tmp = -sum[i] + dp[i - 1];

		if (i <= K) {
			dp[i] = sum[i];
			pq.emplace(tmp, i);
		}
		else { 
			while (!pq.empty()) {
				auto [val, idx] = pq.top();
				if (val < tmp || idx < i - K) pq.pop();
				else break;
			}

			pq.emplace(tmp, i);
			dp[i] = sum[i] + pq.top().first;
		}
	}

	cout << dp[N];
}
