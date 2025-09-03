#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() {
	fastio;

	int A, B, N;
	cin >> A >> B >> N;

	if (B / 10 == 5 || (B / 10) % 2 == 0) cout << -1;
	else if (A % 10 == 9) {//B가 1*, 3*, 7*, 9* 인 소수일 때
		N -= 5;
		cout << A << 7;
		for (int i = 0; i < N; i++) cout << 1;
		cout << B;
	}
	else {
		N -= 4;
		cout << A;
		for (int i = 0; i < N; i++) cout << 1;
		cout << B;
	}
}
