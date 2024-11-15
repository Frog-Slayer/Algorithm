#include <iostream>
#include <vector>
using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	long long N;
	cin >> N;

	vector<long long> pow(40);
	pow[0] = 1;

	for (int i = 1; i < 40; i++) pow[i] = pow[i - 1] * 3;

	long long ans = 0;
	int idx = 0;

	while (N) {
		if (N & 1) ans += pow[idx];

		idx++;
		N >>= 1;
	}

	cout << ans;
}