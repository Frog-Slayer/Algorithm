#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int solve(int cur, int N, int val) { 
	if (cur == N) { 
		return val % 3 == 0;
	}

	int ret = 0;

	for (int i = (cur == 0); i < 3; i++) { 
		ret += solve(cur + 1, N, val * 10 + i);
	}

	return ret;
}

int main() { 
	fastio;

	int N;
	cin >> N;

	int ans = 0;

	ans += solve(0, N, 0);

	cout << ans;
}
