#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main () { 
	fastio;

	int N, K;
	cin >> N >> K;

	vector<int> height(N);

	for (int i = 0; i < N; i++) cin >> height[i]; 
	sort(all(height));

	vector<int> diff;

	for (int i = 1; i < N; i++) diff.emplace_back(height[i] - height[i - 1]);

	sort(all(diff));

	ll ans = 0;

	for (int i = 0; i < N - K; i++) ans += diff[i];

	cout << ans;

}
