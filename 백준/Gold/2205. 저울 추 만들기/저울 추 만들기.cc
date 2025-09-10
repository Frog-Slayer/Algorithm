#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() { 
	fastio;
	
	int N;
	cin >> N;

	vector<int> twos, ans(N + 1);

	for (int i = 1; i <= 2 * N; i *= 2) twos.emplace_back(i);

	int sz = twos.size();

	for (int i = N; i >= 1; i--) { 
		if (ans[i]) continue;

		for (int j = sz - 1; j >= 0; j--) { 
			int target = twos[j];
			int diff = target - i;

			if (0 < diff && diff <= N && !ans[i] && !ans[diff]) { 
				ans[i] = diff;
				ans[diff] = i;
				break;
			}
		}
	}

	for (int i = 1; i <= N; i++) cout << ans[i] << '\n';

}
