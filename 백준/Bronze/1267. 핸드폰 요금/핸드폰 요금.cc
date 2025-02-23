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

	int Y = 0, M = 0;

	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;

		Y += 10 * (n / 30 + 1);
		M += 15 * (n / 60 + 1);
	}

	if (Y < M) cout << "Y " << Y;
	else if (Y == M) cout << "Y M " << Y;
	else cout << "M " << M;
}
