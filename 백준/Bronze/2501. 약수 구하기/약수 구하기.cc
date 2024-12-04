#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)


int main() {
	fastio;

	int N, K;
	cin >> N >> K;

	int cnt = 0;

	for (int i = 1; i <= N; i++) {
		if (N % i == 0) cnt++;

		if (cnt == K){
			cout << i;
			return 0;
		}
	}

	cout << 0;
}