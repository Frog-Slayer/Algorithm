#include <iostream>
#include <vector>
#include <map>
#include <tuple>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

typedef long long ll;

int main() {
	fastio;

	int N;
	cin >> N;

	vector<ll> accsum(N);
	map<int, int> start, end;

	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;

		if (start.find(a) == start.end()) start[a] = i;
		end[a] = i;

		accsum[i] = a + (i ? accsum[i - 1] : 0);
	}

	ll ans = 0;
	int count = 0;

	for (auto [val, idx]: start) {
		ll sum = val;

		sum = accsum[end[val]] - (idx ? accsum[idx - 1] : 0);

		if (ans < sum) {
			ans = sum;
			count = 1;
		}
		else if (ans == sum) count++;
	}

	cout << ans << ' ' << count;
}