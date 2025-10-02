#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main () { 
	fastio;

	int N;
	cin >> N;

	vector<int> a(N), b(N); 

	for (int i = 0; i < N; i++) cin >> a[i]; 
	for (int i = 0; i < N; i++) cin >> b[i]; 

	ll ans = 1;

	sort(all(a), greater());

	for (int i = 0; i < N; i++) { 
		int cnt = 0;

		for (int j = 0; j < N; j++) cnt += b[j] >= a[i];

		ans *= cnt - i;
	}

	cout << ans;
}
