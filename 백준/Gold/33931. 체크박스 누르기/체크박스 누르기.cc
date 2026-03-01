#include <iostream>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main () { 
	fastio;

	int N, M;
	cin >> N >> M;

	if ((M / N) % 2 == 0) cout << M % N;
	else cout << N - (M % N);
}
