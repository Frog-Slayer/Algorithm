#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int len(int a) { 
	int ret = 0;

	while (a) { 
		ret++;
		a /= 10;
	}

	return ret;
}

int main() { 
	fastio;
	
	int N, K;
	cin >> N >> K;

	vector<int> tens(9);
	tens[0] = 1;
	for (int i = 1; i < 9; i++) tens[i] = tens[i - 1] * 10;

	ll ans = 0;

	for (int i = 1; i <= N; i++) { 
		ans = (ans * tens[len(i)] + i) % K;
	}
	
	cout << ans;
}
