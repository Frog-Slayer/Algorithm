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

	vector<int> tip(N);

	for (int i = 0; i < N; i++) { 
		cin >> tip[i];
	}

	sort(all(tip), greater());

	ll ans = 0;

	for (int i = 0; i < N; i++) ans += max(tip[i] - i, 0);

	cout << ans;
}