#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N;
	cin >> N;

	vector<int> v(N);

	for (int i = 0; i < N; i++) {
		int a, b;
		cin >> a >> b;

		v[i] = b - a;
	}

	if (N % 2) cout << 1;
	else {
		sort(all(v));
		cout << v[N / 2] -  v[N / 2 - 1] + 1;
	}
	
}
