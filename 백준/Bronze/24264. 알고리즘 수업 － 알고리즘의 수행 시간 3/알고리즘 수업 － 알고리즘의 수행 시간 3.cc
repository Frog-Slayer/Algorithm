#include <iostream>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int n;
	cin >> n;

	long long ans = n;
	ans *= n;
	cout << ans  << "\n2";
}