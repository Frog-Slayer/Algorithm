#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int N;
	cin >> N;

	vector<string> nums(N);

	for (int i = 0; i < N; i++) cin >> nums[i];

	sort(all(nums), [&](string &s, string &t) { 
			string st = s + t;
			string ts = t + s;
			return st > ts;
	});

	if (nums[0][0] == '0') cout << '0';
	else for (int i = 0; i < N; i++) cout << nums[i];
}
