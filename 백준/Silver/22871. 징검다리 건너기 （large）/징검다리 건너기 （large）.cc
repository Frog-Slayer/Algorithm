#include <iostream>
#include <vector>
using namespace std;
#define fastio cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0)

typedef long long ll;
const int MAX_N = 5000;
int N;
ll dp[MAX_N];

int main() {
	cin >> N;

	vector<ll> A(N);
	for (int i = 0; i < N; i++) cin >> A[i];

	dp[0] = 0;
	for (int i = 1; i < N; i++) {
		dp[i] = 1e6;

		for (int j = 0; j < i; j++) {
			ll power = max(dp[j], (i - j) * (1 + llabs(A[i] - A[j])));
			dp[i] = min(dp[i], power);
		}
	}


	cout << dp[N - 1];
}