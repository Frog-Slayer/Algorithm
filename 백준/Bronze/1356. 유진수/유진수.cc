#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()


int main() { 
	fastio;

	string N;
	cin >> N;

	int len = N.size();

	if (len == 1) { 
		cout << "NO";
		return 0;
	}

	int left = N[0] - '0', right = 1;
	int right_zero_count = 0;

	for (int i = 1; i < len; i++) { 
		int n = N[i] - '0';
		if (n) right *= n;
		else right_zero_count++;
	}

	bool yes = (left == (right * (right_zero_count ? 0 : 1)));

	for (int i = 1; i < len - 1 && !yes; i++) { 
		int n = N[i] - '0';
		left *= n;

		if (n) right /= n;
		else right_zero_count--;

		yes = (left == (right * (right_zero_count ? 0 : 1)));
	}

	cout << (yes ? "YES" : "NO");
	

}