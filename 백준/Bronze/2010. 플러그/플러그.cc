#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int N;
	cin >> N;

	int sum = 0;

	for (int i = 0; i < N; i++) { 
		int c;
		cin >> c;
		sum += c;
	}

	sum -= (N - 1);

	cout << sum;
}
