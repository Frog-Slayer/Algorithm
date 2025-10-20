#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() { 
	fastio;

	string N;
	int M;
	cin >> N >> M;

	int n_len = N.size();
	int cnt = min(M, n_len * stoi(N));

	for (int i = 0, j = 0; i < cnt; i++, j = (j + 1) % n_len) { 
		cout << N[j];
	}
}