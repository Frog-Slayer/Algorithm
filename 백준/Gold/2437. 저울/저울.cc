#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main () { 
	fastio;

	int N;
	cin >> N;

	vector<int> w(N);

	for (int i = 0; i < N; i++) cin >> w[i]; 

	sort(all(w));

	int ans = 0;

	for (int i = 0; i < N; i++) { 
		if (w[i] > ans + 1) break;
		ans += w[i];
	}

	cout << ans + 1;
}