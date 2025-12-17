#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int to_score(int a) { 
	string s = to_string(a);
	int ret = 0;

	for (char c : s) { 
		ret += (c - '0');
	}

	return ret;
}

int main() { 
	fastio;

	int N;
	cin >> N;

	map<int, int> s;

	int a;

	for (int i = 0; i < N; i++) { 
		cin >> a;
		s[a]++;
	}

	int ans = 0;

	for (auto &[a, ca] : s) { 
		for (auto &[b, cb] : s) { 
			if (a == b && ca == 1) continue;
			int mp = a * b;
			ans = max(ans, to_score(mp));
		}
	}
	
	cout << ans;
}
