#include <iostream>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	int K;
	cin >> K;

	int b = 0;

	while ((1 << b) < K) b++;

	cout << (1 << b) << ' ';

	int c = 0;

	for (int i = b; i >= 0 && K; i--) {
		K &= ~(1 << i);
		c++;
	}

	cout << --c;
}
