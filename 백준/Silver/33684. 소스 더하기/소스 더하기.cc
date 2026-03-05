#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main () { 
	fastio;

	int N, K;
	cin >> N >> K;

	vector<int> A(N);

	for (int i = 0; i < N; i++) cin >> A[i];

	sort(all(A));

	if (A[N - 1] > K) cout << 0;
	else if (A[0] <= 0) cout << -1;
	else { 
		long long cnt = 0;

		for (int i = 1; i < N; i++) cnt += (K - A[i]) / A[0];

		cout << ++cnt;
	}
}