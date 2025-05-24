#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int n;
	cin >> n;

	vector<int> x(n);

	for (int i = 0; i < n; i++) {
		cin >> x[i];
	}

	long long ret = 0;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			ret += llabs(x[i] - x[j]);
		}
	}

	ret *= 2;

	cout << ret;
}
