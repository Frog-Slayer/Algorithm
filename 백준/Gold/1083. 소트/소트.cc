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

	vector<int> array(N);

	for (int i = 0; i < N; i++) cin >> array[i];

	int S;
	cin >> S;

	int offset = 0;

	while (S && offset < N) {
		int mx = array[offset], mx_idx = offset;
		int i;

		for (i = 0; i <= S && i + offset < N; i++) {
			if (array[i + offset] > mx) {
				mx = array[i + offset];
				mx_idx = i + offset;
			}
		}

		for (int i = mx_idx; i > offset; i--) swap(array[i], array[i - 1]);

		S -= (mx_idx - offset);

		offset++;
	}

	for (int i = 0; i < N; i++) cout << array[i] << ' ';
}
