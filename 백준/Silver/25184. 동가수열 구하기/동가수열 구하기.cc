#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int N;
	cin >> N;

	int a = N, b = (N + 1)/ 2;

	for (int i = 0; i < N; i++) { 
		if (i % 2) cout << a-- << ' ';
		else cout << b-- << ' ';
	}

}
