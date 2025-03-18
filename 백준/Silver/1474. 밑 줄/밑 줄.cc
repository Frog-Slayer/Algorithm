#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N, M;
	cin >> N >> M;

	int len = 0;

	vector<string> v(N);

	for (int i = 0; i < N; i++) {
		cin >> v[i];
		len += v[i].length();
	}

	int underscore = (M - len) / (N - 1);
	int left = (M - len) - (underscore * (N - 1));

	for (int i = 1; i < N; i++) {
		cout << v[i - 1];
		for (int j = 0; j < underscore; j++) cout << '_';

		if (left && (v[i][0] >= 'a' || i >= N - left)) {
			cout << '_';
			left--;
		}
	}

	cout << v[N - 1] << '\n';

	
}
