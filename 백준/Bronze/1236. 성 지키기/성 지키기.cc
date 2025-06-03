#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	int N, M;
	cin >> N >> M;

	cin.ignore();

	vector<string> v(N);
	vector<bool> rowWithX(N), colWithX(M);

	for (int i = 0; i < N; i++) cin >> v[i];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (v[i][j] == 'X') {
				rowWithX[i] = true;
				colWithX[j] = true;
			}
		}
	}

	int noXrow = 0, noXcol = 0;
	for (int i = 0; i < N; i++) noXrow += !rowWithX[i];
	for (int i = 0; i < M; i++) noXcol += !colWithX[i];

	cout << max(noXrow, noXcol);
}
