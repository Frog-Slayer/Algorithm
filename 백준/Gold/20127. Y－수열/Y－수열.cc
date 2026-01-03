#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int N;
	cin >> N;

	vector<int> a(N + 1);

	for (int i = 1; i <= N; i++){ 
		cin >> a[i]; 
	}

	int aug_cnt = 0, dim_cnt = 0;
	int aug_k = 0, dim_k = 0;

	for (int i = 1; i < N; i++) { 
		if (a[i] < a[i + 1]) { 
			aug_cnt++;
			aug_k = i;
		}
		if (a[i] > a[i + 1]) { 
			dim_cnt++;
			dim_k = i;
		}
	}

	int ans = INT_MAX;

	if (aug_cnt == 0 || dim_cnt == 0) ans = 0;
	if (a[1] >= a[N] && dim_cnt == 1) ans = min(ans, dim_k);
	if (a[1] <= a[N] && aug_cnt == 1) ans = min(ans, aug_k);

	cout << (ans == INT_MAX ? -1 : ans);

}
