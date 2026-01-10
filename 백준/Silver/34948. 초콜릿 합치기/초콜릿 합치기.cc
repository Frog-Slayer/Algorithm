#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() { 
	fastio;

	int N;
	cin >> N;

	vector<pair<ll, ll>> chocolate(N);

	for (int i = 0; i < N; i++) { 
		cin >> chocolate[i].first;
	}

	for (int i = 0; i < N; i++) { 
		cin >> chocolate[i].second;
	}


	sort(all(chocolate), greater<>());

	for (int i = 1; i < N; i++) { 
		chocolate[i].second += chocolate[i - 1].second;
	}

	long long ans = 0;

	for (int i = 0, j = 0; i < N; i = j) { 
		while (j < N && chocolate[j].first == chocolate[i].first) j++;

		ans = max(ans, chocolate[j - 1].first * chocolate[j - 1].second);
	}

	cout << ans;


}
