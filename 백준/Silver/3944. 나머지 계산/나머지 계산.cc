#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int T;
	cin >> T;

	for (int i = 0; i < T; i++) { 
		int B;
		string D;
		cin >> B >> D;

		int sum = 0;
		for (char &t : D) sum += t - '0';

		cout << sum % (B - 1) << '\n';

	}
}

