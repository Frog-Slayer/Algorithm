#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int N;
	cin >> N;

	vector<int> a, b;

	for (; N; N -= 3) { 
		if (N < 3) break;
		a.emplace_back(N);
		b.emplace_back(N - 1);
		b.emplace_back(N - 2);
	}

	if (N == 2) { 
		a.emplace_back(1);
		b.emplace_back(2);
	}

	cout << a.size() << '\n';
	for (int i = a.size() - 1; i >= 0; i--) cout << a[i] << ' ';

	cout << '\n' << b.size() << '\n';
	for (int i = b.size() - 1; i >= 0; i--) cout << b[i] << ' ';

}
