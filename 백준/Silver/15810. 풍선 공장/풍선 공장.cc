#include <iostream>
#include <vector>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() { 
	fastio;

	int N, M;
	cin >> N >> M;

	vector<int> A(N);

	for (int i = 0; i < N; i++) cin >> A[i];

	ll left = 0;
	ll right = 1000000LL * 1000000LL;

	while (left < right) { 
		ll mid = (left + right) / 2;
		ll sum = 0;

		for (int i = 0; i < N; i++) { 
			sum += (mid / A[i]);
		}

		if (sum >= M) right = mid;
		else left = mid + 1;
	}

	cout << right;
}