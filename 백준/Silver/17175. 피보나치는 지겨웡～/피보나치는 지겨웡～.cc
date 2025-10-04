#include <iostream>
#include <cmath>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int MOD = 1000000007;

int cnt[51];

int main () { 
	fastio;

	int N;
	cin >> N;

	cnt[0] = cnt[1] = 1;
	for (int i = 2; i <= N; i++){ 
		cnt[i] = 1 + cnt[i - 1] + cnt[i - 2]; 
		cnt[i] %= MOD;
	}

	cout << cnt[N];
}
