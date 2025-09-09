#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() { 
	fastio;

	int T;
	cin >> T;

	while (T--) { 
		int K;
		cin >> K;

		priority_queue<ll, vector<ll>, greater<>> pq;
		ll ans = 0;

		for (int i = 0; i < K; i++) { 
			int c;
			cin >> c;
			pq.emplace(c);
		}

		while (pq.size() > 1) { 
			ll first = pq.top();
			pq.pop();
			ll second = pq.top();
			pq.pop();

			ans += (first + second);
			pq.emplace(first + second);
		}
		
		
		cout << ans << '\n';
	}
	
}
