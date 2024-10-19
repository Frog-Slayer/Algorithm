#include <iostream>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;
	string A, B;
	cin >> A >> B;

	int alen = A.length(), blen = B.length();
	int min_diff = 50;

	for (int i = 0; i <= blen - alen; i++) {
		int diff = 0;

		for (int a = 0; a < alen; a++) {
			if (A[a] != B[i + a]) diff++;
		}

		min_diff = min(min_diff, diff);
	}

	cout << min_diff;

}