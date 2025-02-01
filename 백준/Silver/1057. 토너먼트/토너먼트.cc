#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	int N;
	cin >> N;

	int jimin, hansu;
	cin >> jimin >> hansu;

	int ans = 0;

	while (jimin != hansu) {
		jimin -= jimin / 2;
		hansu -= hansu / 2;
		ans++;
	}

	cout << ans;
}