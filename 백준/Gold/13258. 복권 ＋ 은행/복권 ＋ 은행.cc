#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() {
	fastio;

	int N;
	cin >> N;


	vector<int> account(N);
	int total = 0;

	for (int i = 0; i < N; i++) { 
		cin >> account[i]; 
		total += account[i];
	}

	int J, C;
	cin >> J >> C;

	double expected = (double)account[0]/total * J;

	cout << fixed;
	cout.precision(12);
	cout << account[0] + expected * C;

}
