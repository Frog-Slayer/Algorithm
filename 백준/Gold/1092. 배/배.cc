#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N;
	cin >> N;

	vector<int> crane(N);

	for (int i = 0; i < N; i++) cin >> crane[i];

	int M;
	cin >> M;
	vector<int> freight(M);

	for (int i = 0; i < M; i++) cin >> freight[i];

	sort(all(crane), greater());
	sort(all(freight), greater());

	int ans = 0;

	if (crane.front() < freight.front()) ans = -1;
	else {
		while (M) {
			int cur = 0;
			for (int &c : crane) {
				if (!M) break;
				for (; cur < freight.size(); cur++) {
					if (!freight[cur]) continue;
					if (c >= freight[cur]) {
						M--;
						freight[cur] = 0;
						break;
					}
				}
			}
			ans++;
		}
	}
	

	cout << ans;
}