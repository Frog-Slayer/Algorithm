#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int N, K;
	cin >> N >> K;

	vector<int> v(N);

	for (int i = 0; i < N; i++) { 
		int a, b;
		cin >> a >> b;

		v[i] = b - a;
	}

	sort(all(v));

	cout << max(0, v[K - 1]);

}
