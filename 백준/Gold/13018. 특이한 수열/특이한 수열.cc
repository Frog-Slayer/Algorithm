#include <iostream>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N, K;
	cin >> N >> K;

	if (K == 1 || N == K) cout << "Impossible";
	else { 
		cout << N - K << ' ';
		for (int i = 1; i < N - K; i++) cout << i << ' ';
		for (int i = N - K + 1; i <= N; i++) cout << i << ' ';
	}
}