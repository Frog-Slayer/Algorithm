#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)


int main() {
	fastio;

	int N, L, C;
	cin >> N >> L >> C;

	int mx = (C + 1)/(L + 1);
	if (mx % 13 == 0) mx--;

	int ans = N / mx;
	int remain = N % mx;

	if (!remain) cout << ans;
	else {
		if (remain % 13 == 0) {
			bool adj = false;
			if (ans) {

				int newremain = remain + 1;
				int adjusted = mx - 1;

				if (newremain % 13 && adjusted % 13) adj = true;
			}

			ans += adj ? 1 : 2;
		}
		else ans ++;

		cout << ans;
	}

}
