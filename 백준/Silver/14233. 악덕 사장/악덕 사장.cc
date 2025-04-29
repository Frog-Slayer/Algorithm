#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N;
	cin >> N;

	vector<int> A(N + 1);

	for (int i = 1; i <= N; i++) cin >> A[i];

	sort(all(A));

	int ans = INT_MAX;

	for (int i = 1; i <= N; i++) ans = min(ans, A[i]/i);
	
	cout << ans;

}
