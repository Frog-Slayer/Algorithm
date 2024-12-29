#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N, M;
	cin >> N >> M;

	vector<string> v(N);

	for (int i = 0; i < N; i++) {
		cin >> v[i];
		reverse(all(v[i]));
	}

	for (int i = 0; i < N; i++) cout << v[i] << '\n';

}