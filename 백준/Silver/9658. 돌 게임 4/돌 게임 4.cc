#include <iostream>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	int N;
	cin >> N;

	if (N % 7 == 1 || N % 7 == 3) cout << "CY";
	else cout << "SK";
}
