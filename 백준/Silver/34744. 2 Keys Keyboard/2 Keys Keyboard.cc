#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int N;
	cin >> N;

	int ans = 0;
	int d = 2;

	while (N > 1) { 
		while (N % d == 0) { 
			ans += d;
			N /= d;
		}
		d++;
	}
	cout << ans;
}
